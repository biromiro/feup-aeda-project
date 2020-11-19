//
// Created by emanu on 18-Nov-20.
//

#ifndef PROJECT_USERALREADYEXISTS_H
#define PROJECT_USERALREADYEXISTS_H

#include <iostream>
#include <exception>
#include <memory>
#include "../../model/user/user.h"

class UserAlreadyExists : public std::invalid_argument{
public:
    UserAlreadyExists(std::shared_ptr<User> user, const std::string & message);
    [[nodiscard]] const std::shared_ptr<User> &getUser() const;

private:
    std::shared_ptr<User> user;
};

#endif //PROJECT_USERALREADYEXISTS_H
