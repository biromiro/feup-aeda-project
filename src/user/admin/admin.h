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

    /**
     * Getter of the type of User
     *
     * @return the user's type (in this case, ADMIN)
     */
    enum UserTypes getUserType() const override;
};

#define PROJECT_ADMIN_H

#endif //PROJECT_ADMIN_H
