//
// Created by biromiro on 27/10/20.
//

#ifndef PROJECT_USER_MANAGER_H
#include <ostream>
#include <unordered_set>
#include "user.h"
#include "memory"
#include "admin/admin.h"
#include <fstream>

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
    bool add(const std::shared_ptr<User>& user);

    /**
     * Removes a user from the users unordered set
     *
     * @param user user to be removed
     * @return True if the action was successful, false otherwise
     */
    bool remove(const std::shared_ptr<User>& user);

    /**
     * Checks if the user exists in the users unordered set
     *
     * @param user user to be found
     * @return True if the action was successful, false otherwise
     */
    bool has(const std::shared_ptr<User>& user) const;

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
    std::shared_ptr<User> get(std::string nickname) const;

    /**
     * Getter of the users unordered set
     *
     * @return the unordered set of users
     */
    std::unordered_set<std::shared_ptr<User>> getUsers() const;

private:
    std::unordered_set<std::shared_ptr<User>> users;
};
#define PROJECT_USER_MANAGER_H

#endif //PROJECT_USER_MANAGER_H
