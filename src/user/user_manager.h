//
// Created by biromiro on 27/10/20.
//

#ifndef PROJECT_USER_MANAGER_H
#include <ostream>
#include <unordered_set>
#include "user.h"

class UserManager{
public:

    /**
     * Default constructor of the UserManager class
     */
    UserManager();

    /**
     * Adds a new user to the users unordered set
     *
     * @param user new user to be added
     * @return True if the action was successful, false otherwise
     */
    bool add(User* user);

    /**
     * Removes a user from the users unordered set
     *
     * @param user user to be removed
     * @return True if the action was successful, false otherwise
     */
    bool remove(User* user);

    /**
     * Checks if the user exists in the users unordered set
     *
     * @param user user to be found
     * @return True if the action was successful, false otherwise
     */
    bool has(User* user) const;

    /**
     * Checks, by nickname (which is unique), if the user exists in the users unordered set
     *
     * @param nickname the nickname of the user to be found
     * @return True if the action was successful, false otherwise
     */
    bool has(std::string nickname) const;

    /**
     * Returns the pointer to a user given his nickname
     *
     * @param nickname the nickname of the user to be found and returned
     * @return the user with the given nickname
     */
    User* get(std::string nickname) const;

private:
    std::unordered_set<User*> users;
};
#define PROJECT_USER_MANAGER_H

#endif //PROJECT_USER_MANAGER_H
