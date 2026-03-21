#ifndef DA_PROJECT_REVIEWER_H
#define DA_PROJECT_REVIEWER_H

#include <string>

class Reviewer {
private:
    int id;
    std::string name;
    std::string email;
    int primaryExpertise;
    int secondaryExpertise; //-1 ou 0 if it doesn't exist

public:
    Reviewer(int id, std::string name, std::string email, int primaryExpertise, int secondaryExpertise = -1)
        : id(id), name(std::move(name)), email(std::move(email)),
          primaryExpertise(primaryExpertise), secondaryExpertise(secondaryExpertise) {}

    // Getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    int getPrimaryExpertise() const { return primaryExpertise; }
    int getSecondaryExpertise() const { return secondaryExpertise; }
};

#endif //DA_PROJECT_REVIEWER_H