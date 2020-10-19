//
// Created by biromiro on 18/10/20.
//

#include "admin.h"

Admin::Admin(unsigned int age, std::string name, std::string nickname): User(age,name,nickname, ADMIN) {}

enum UserTypes Admin::getUserType() const{
    return type;
}