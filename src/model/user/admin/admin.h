//
// Created by biromiro on 18/10/20.
//

#include "../user.h"

#ifndef PROJECT_ADMIN_H

/**
 * @file admin.cpp
 *
 * @brief Class representing the Admin class
 *
 * @ingroup user
 */

/**
 * Implementation of the Admin class
 *
 * The admin has access, through the UI, to another statistics that other users do not have.
 * There can only be one instance of the Admin class per platform
 */
class Admin: public User{
public:

    Admin();

    /**
     * Constructor of the Admin class
     *
     * @param birthDate the birth date of the admin
     * @param name the name of the admin
     * @param nickname the nickname of the admin
     */
    Admin(Date birthDate, std::string name, std::string nickname, std::string password);

    /**
     * Reads saved admins from File
     * @param ifs File to read admin data from
     * */
    void readData(std::ifstream& ifs) override;

    /**
    * Writes and updates admins to File
    * @param ifs File to save admins to
    * */
    void writeData(std::ofstream& ofs) override;
};

#define PROJECT_ADMIN_H

#endif //PROJECT_ADMIN_H
