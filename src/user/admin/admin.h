//
// Created by biromiro on 18/10/20.
//

#include "../user.h"

#ifndef PROJECT_ADMIN_H

class Admin: public User{
public:
    /**
     * Constructor of the Admin class
     *
     * @param birthDate the birth date of the admin
     * @param name the name of the admin
     * @param nickname the nickname of the admin
     */
    Admin(Date birthDate, std::string name, std::string nickname);
};

#define PROJECT_ADMIN_H

#endif //PROJECT_ADMIN_H
