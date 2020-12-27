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

/**
 * @file user_manager.cpp
 *
 * @brief Class representing the User Manager class
 *
 * @ingroup user
 */

struct userHash{
    int operator()(const std::shared_ptr<User>& str) const{
        int v = 0;
        for(const auto& elem: str->getNickname()){
            v = v*37 + elem;
        }
        return v;
    }
    bool operator()(const std::shared_ptr<User>& str, const std::shared_ptr<User>& str2) const{
        return str->getNickname() == str2->getNickname();
    }
};

typedef std::unordered_set<std::shared_ptr<User>,userHash,userHash> tabHUser;

/**
 * Implementation of the User Manager class
 *
 * Manages all users, functioning as a databse for no nickname repetition (which must be unique)
 */
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
    tabHUser getUsers() const;

private:
    tabHUser users;
};
#define PROJECT_USER_MANAGER_H

#endif //PROJECT_USER_MANAGER_H
