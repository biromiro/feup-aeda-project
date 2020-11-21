//
// Created by biromiro on 15/11/20.
//

#ifndef PROJECT_CURRENTSESSION_H
#define PROJECT_CURRENTSESSION_H

#include <iostream>
#include "../model/user/user_manager.h"

/**
 * @file currentSession.cpp
 *
 * @brief Holds the current session of the UI
 *
 * @ingroup auth
 */

/**
 * Implementation of the current session class
 *
 * Holds the current session information
 */
class CurrentSession{
private:
    std::shared_ptr<UserManager> userManager;
    std::shared_ptr<User> currentUser;
public:
    /**
     * Current Session's default constructor
     */
    CurrentSession();

    /**
     * Current Session's constructor
     * @param userManager the user manager of the platform
     */
    explicit CurrentSession(std::shared_ptr<UserManager> userManager);

    /**
     * Tries to log in via a given nickname and password
     *
     * @param nickname the nickname given
     * @param password the password given
     * @return true if it was sucessful, false othewise
     */
    bool login(std::string nickname, const std::string& password);

    /**
     * Tries to log out the current usert
     *
     * @return true if it was sucessful, false othewise
     */
    bool logout();

    /**
     * Gets the current User logged int
     *
     * @return the shared pointer to the current user
     */
    [[nodiscard]] const std::shared_ptr<User> &getCurrentUser() const;


    /**
     * Gets the nickname of the current user
     *
     * @return the nickname of the current user
     */
    [[nodiscard]] std::string getNickname() const;
};

#endif //PROJECT_CURRENTSESSION_H
