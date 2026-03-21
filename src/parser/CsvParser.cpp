#include "../../include/parser/CsvParser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

CsvParser::CsvParser(std::string filename) : filename(std::move(filename)) {}

// Remove espaços em branco nas pontas
std::string CsvParser::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n\"");
    if (std::string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\r\n\"");
    return str.substr(first, (last - first + 1));
}

// Ignora tudo depois do '#' (comentários) [cite: 44]
std::string CsvParser::removeComments(const std::string& line) {
    size_t pos = line.find('#');
    if (pos != std::string::npos) {
        return line.substr(0, pos);
    }
    return line;
}

// Divide a linha por vírgulas, lidando rudimentarmente com aspas
std::vector<std::string> CsvParser::splitCsvLine(const std::string& line) {
    std::vector<std::string> tokens;
    std::string current;
    bool inQuotes = false;
    
    for (char c : line) {
        if (c == '\"') {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            tokens.push_back(trim(current));
            current.clear();
        } else {
            current += c;
        }
    }
    tokens.push_back(trim(current));
    return tokens;
}

bool CsvParser::parse() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o ficheiro " << filename << std::endl;
        return false;
    }

    std::string line;
    enum State { NONE, SUBMISSIONS, REVIEWERS, PARAMETERS, CONTROL };
    State currentState = NONE;

    int lineNum = 0;

    while (std::getline(file, line)) {
        lineNum++;
        
        // Verifica se é uma mudança de secção 
        std::string trimmedLine = trim(line);
        if (trimmedLine == "#Submissions") { currentState = SUBMISSIONS; continue; }
        if (trimmedLine == "#Reviewers") { currentState = REVIEWERS; continue; }
        if (trimmedLine == "#Parameters") { currentState = PARAMETERS; continue; }
        if (trimmedLine == "#Control") { currentState = CONTROL; continue; }
        if (trimmedLine == "#") { currentState = NONE; continue; } // Separador vazio [cite: 41, 49]

        // Limpa a linha de comentários (ignorando tudo após o '#' que não seja marcador de secção) [cite: 44]
        std::string cleanLine = removeComments(line);
        if (trim(cleanLine).empty()) continue; // Linha vazia ou só comentário

        std::vector<std::string> tokens = splitCsvLine(cleanLine);

        try {
            if (currentState == SUBMISSIONS) {
                // Id, Title, Authors, E-mail, Primary, Secondary [cite: 39, 47]
                if (tokens.size() < 5) continue; // Precisa pelo menos do primário
                int id = std::stoi(tokens[0]);
                
                // Validação de IDs únicos 
                if (submissionIds.find(id) != submissionIds.end()) {
                    std::cerr << "Erro na linha " << lineNum << ": Submission ID duplicado (" << id << ")." << std::endl;
                    return false;
                }
                submissionIds.insert(id);

                int primary = std::stoi(tokens[4]);
                int secondary = (tokens.size() >= 6 && !tokens[5].empty()) ? std::stoi(tokens[5]) : -1;
                
                submissions.emplace_back(id, tokens[1], tokens[2], tokens[3], primary, secondary);
            } 
            else if (currentState == REVIEWERS) {
                // Id, Name, E-mail, Primary, Secondary [cite: 40, 51]
                if (tokens.size() < 4) continue;
                int id = std::stoi(tokens[0]);

                if (reviewerIds.find(id) != reviewerIds.end()) {
                    std::cerr << "Erro na linha " << lineNum << ": Reviewer ID duplicado (" << id << ")." << std::endl;
                    return false;
                }
                reviewerIds.insert(id);

                int primary = std::stoi(tokens[3]);
                int secondary = (tokens.size() >= 5 && !tokens[4].empty()) ? std::stoi(tokens[4]) : -1;

                reviewers.emplace_back(id, tokens[1], tokens[2], primary, secondary);
            }
            else if (currentState == PARAMETERS || currentState == CONTROL) {
                if (tokens.size() < 2) continue;
                std::string key = tokens[0];
                std::string value = tokens[1];

                if (key == "MinReviewsPerSubmission") config.setMinReviewsPerSubmission(std::stoi(value));
                else if (key == "MaxReviewsPerReviewer") config.setMaxReviewsPerReviewer(std::stoi(value));
                else if (key == "GenerateAssignments") config.setGenerateAssignments(std::stoi(value));
                else if (key == "RiskAnalysis") config.setRiskAnalysis(std::stoi(value));
                else if (key == "OutputFileName") config.setOutputFileName(value);
                // Os dominios globais podem ser adicionados à config se necessário
            }
        } catch (const std::exception& e) {
            std::cerr << "Erro de formatacao na linha " << lineNum << ": " << cleanLine << std::endl;
            return false;
        }
    }

    file.close();
    return true;
}