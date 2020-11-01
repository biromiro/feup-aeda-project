//
// Created by biromiro on 27/10/20.
//

#ifndef PROJECT_ADMIN_MANAGER_H
#define PROJECT_ADMIN_MANAGER_H

#include "admin.h"
#include "../user_manager.h"


class AdminManager{
public:
    /**
     * Constructor of Admin Manager class
     *
     * @param userManager the user manager
     */
    explicit AdminManager(UserManager* userManager);

    /**
     * Adds/Updates the admin to manage
     *
     * @param admin the admin to add
     * @return True if the action was successful, false otherwise
     */
    bool add(Admin* admin);

    /**
     * Removes the current admin
     *
     * @param admin the admin to remove
     * @return True if the action was successful, false otherwise
     */
    bool remove(Admin* admin);

    /**
     * Checks if the admin is the one given as parameter
     *
     * @param admin the admin to check
     * @return True if the action was successful, false otherwise
     */
    bool is(Admin* admin) const;

    /**
     * Checks if the admin has the nickname (which is unique) given as parameter
     *
     * @param nickname the nickname to check
     * @return True if the action was successful, false otherwise
     */
    bool is(std::string nickname) const;

    /**
     * Getter of the admin
     *
     * @return the current admin
     */
    Admin* get() const;

    ~AdminManager();
private:
    Admin* admin;
    UserManager* userManager;
    static unsigned int noInstances;
};

#endif //PROJECT_ADMIN_MANAGER_H
