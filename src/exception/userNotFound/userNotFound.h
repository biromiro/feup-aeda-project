//
// Created by emanu on 19-Nov-20.
//

#ifndef PROJECT_USERNOTFOUND_H
#define PROJECT_USERNOTFOUND_H

#include <iostream>
#include <exception>
#include <memory>
#include "../../model/user/user.h"

class UserNotFound : std::invalid_argument{
public:
    UserNotFound(std::shared_ptr<User> user, const std::string & message);
    const std::string & getMessage();
private:
    std::shared_ptr<User> user;
    std::string message;

};


#endif //PROJECT_USERNOTFOUND_H
