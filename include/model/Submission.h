/**
 * @file Submission.h
 * @brief Header file for the Submission class.
 * * This file defines the Submission class, which represents a paper or work
 * submitted to the conference.
 */

#ifndef DA_PROJECT_SUBMISSION_H
#define DA_PROJECT_SUBMISSION_H

#include <string>
#include <utility>

/**
 * @class Submission
 * @brief Represents a paper submitted to the conference.
 * * This class stores all relevant information about a submission, including its
 * unique identifier, title, authors, contact email, and expertise topics.
 */
class Submission {
private:
    int id;                     ///< Unique identifier for the submission.
    std::string title;          ///< Title of the paper.
    std::string authors;        ///< List of authors (usually comma-separated).
    std::string email;          ///< Contact email of the corresponding author.
    int primaryTopic;           ///< ID of the primary expertise topic required.
    int secondaryTopic;         ///< ID of the secondary expertise topic (optional, -1 or 0 if none).

public:
    /**
     * @brief Constructor for the Submission class.
     * @param id Unique ID of the submission.
     * @param title Title of the paper.
     * @param authors Authors of the paper.
     * @param email Contact email.
     * @param primaryTopic ID of the primary topic.
     * @param secondaryTopic ID of the secondary topic (defaults to -1).
     */
    Submission(int id, std::string title, std::string authors, std::string email, int primaryTopic, int secondaryTopic = -1)
        : id(id), title(std::move(title)), authors(std::move(authors)), email(std::move(email)),
          primaryTopic(primaryTopic), secondaryTopic(secondaryTopic) {}

    /**
     * @brief Gets the submission ID.
     * @return The unique identifier of the submission.
     */
    int getId() const { return id; }

    /**
     * @brief Gets the submission title.
     * @return A string containing the title.
     */
    std::string getTitle() const { return title; }

    /**
     * @brief Gets the authors of the submission.
     * @return A string with the author names.
     */
    std::string getAuthors() const { return authors; }

    /**
     * @brief Gets the contact email.
     * @return A string with the email address.
     */
    std::string getEmail() const { return email; }

    /**
     * @brief Gets the primary topic ID.
     * @return The ID of the primary topic.
     */
    int getPrimaryTopic() const { return primaryTopic; }

    /**
     * @brief Gets the secondary topic ID.
     * @return The ID of the secondary topic, or -1/0 if not applicable.
     */
    int getSecondaryTopic() const { return secondaryTopic; }
};

#endif //DA_PROJECT_SUBMISSION_H