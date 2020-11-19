//
// Created by emanu on 18-Nov-20.
//

#ifndef PROJECT_USERALREADYEXISTS_H
#define PROJECT_USERALREADYEXISTS_H

#include <iostream>
#include <exception>
#include <memory>
#include "../../model/user/user.h"

class UserAlreadyExists : std::invalid_argument{
public:
    UserAlreadyExists(std::shared_ptr<User> user, const std::string & message);
    const std::string & getMessage();
private:
    std::shared_ptr<User> user;
    std::string message;
};

#endif //PROJECT_USERALREADYEXISTS_H
