/**
 * @file Reviewer.h
 * @brief Header file for the Reviewer class.
 * * This file defines the Reviewer class, which represents a conference reviewer
 * with specific expertise areas.
 */

#ifndef DA_PROJECT_REVIEWER_H
#define DA_PROJECT_REVIEWER_H

#include <string>
#include <utility>

/**
 * @class Reviewer
 * @brief Represents a reviewer in the conference assignment system.
 * * This class stores a reviewer's personal information and their expertise levels
 * in different topics, which are essential for the assignment algorithm.
 */
class Reviewer {
private:
    int id;                     ///< Unique identifier for the reviewer.
    std::string name;           ///< Full name of the reviewer.
    std::string email;          ///< Professional contact email.
    int primaryExpertise;       ///< ID of the primary expertise topic.
    int secondaryExpertise;     ///< ID of the secondary expertise topic (optional, -1 or 0 if none).

public:
    /**
     * @brief Constructor for the Reviewer class.
     * @param id Unique ID of the reviewer.
     * @param name Full name of the reviewer.
     * @param email Contact email.
     * @param primaryExpertise ID of the primary expertise topic.
     * @param secondaryExpertise ID of the secondary expertise topic (defaults to -1).
     */
    Reviewer(int id, std::string name, std::string email, int primaryExpertise, int secondaryExpertise = -1)
        : id(id), name(std::move(name)), email(std::move(email)),
          primaryExpertise(primaryExpertise), secondaryExpertise(secondaryExpertise) {}

    /**
     * @brief Gets the reviewer ID.
     * @return The unique identifier of the reviewer.
     */
    int getId() const { return id; }

    /**
     * @brief Gets the reviewer's name.
     * @return A string containing the full name.
     */
    std::string getName() const { return name; }

    /**
     * @brief Gets the reviewer's email.
     * @return A string with the email address.
     */
    std::string getEmail() const { return email; }

    /**
     * @brief Gets the primary expertise topic ID.
     * @return The ID of the primary expertise area.
     */
    int getPrimaryExpertise() const { return primaryExpertise; }

    /**
     * @brief Gets the secondary expertise topic ID.
     * @return The ID of the secondary expertise area, or -1/0 if not applicable.
     */
    int getSecondaryExpertise() const { return secondaryExpertise; }
};

#endif //DA_PROJECT_REVIEWER_H