//
// Created by biromiro on 18/10/20.
//

#include "../user.h"

#ifndef PROJECT_ADMIN_H

class Admin: public User{
public:
    Admin(unsigned int age, std::string name, std::string nickname);
    enum UserTypes getUserType() const override;
};

#define PROJECT_ADMIN_H

#endif //PROJECT_ADMIN_H
