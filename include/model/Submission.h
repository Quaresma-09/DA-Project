#ifndef DA_PROJECT_SUBMISSION_H
#define DA_PROJECT_SUBMISSION_H

#include <string>

class Submission {
private:
    int id;
    std::string title;
    std::string authors;
    std::string email;
    int primaryTopic;
    int secondaryTopic; //-1 ou 0 if it doesn't exist

public:
    Submission(int id, std::string title, std::string authors, std::string email, int primaryTopic, int secondaryTopic = -1)
        : id(id), title(std::move(title)), authors(std::move(authors)), email(std::move(email)),
          primaryTopic(primaryTopic), secondaryTopic(secondaryTopic) {}

    // Getters
    int getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getAuthors() const { return authors; }
    std::string getEmail() const { return email; }
    int getPrimaryTopic() const { return primaryTopic; }
    int getSecondaryTopic() const { return secondaryTopic; }
};


#endif //DA_PROJECT_SUBMISSION_H