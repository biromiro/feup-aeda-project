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
     * Creates an object of class Admin
     *
     * @param birthDate the birthdate of the admin
     * @param name the name of the admin
     * @param nickname the nickname of the admin
     * @return True if the action was successful, false otherwise
     */
    bool build(Date birthDate, const std::string& name, const std::string& nickname);

    /**
     * Adds/Updates the admin to manage
     *
     * @param admin the admin to add
     * @return True if the action was successful, false otherwise
     */
    bool add(const std::shared_ptr<Admin>& admin);

    /**
     * Removes the current admin
     *
     * @param admin the admin to remove
     * @return True if the action was successful, false otherwise
     */
    bool remove();

    /**
     * Checks if the admin is the one given as parameter
     *
     * @param admin the admin to check
     * @return True if the action was successful, false otherwise
     */
    bool is(const std::shared_ptr<Admin>& admin) const;

    /**
     * Checks if the admin has the nickname (which is unique) given as parameter
     *
     * @param nickname the nickname to check
     * @return True if the action was successful, false otherwise
     */
    bool is(const std::string& nickname) const;

    /**
     * Getter of the admin
     *
     * @return the current admin
     */
    std::shared_ptr<Admin> get() const;

    ~AdminManager();
private:
    std::shared_ptr<Admin> admin;
    UserManager* userManager;
    static unsigned int noInstances;
};

#endif //PROJECT_ADMIN_MANAGER_H
