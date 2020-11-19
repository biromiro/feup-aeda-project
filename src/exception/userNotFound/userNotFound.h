//
// Created by emanu on 19-Nov-20.
//

#ifndef PROJECT_USERNOTFOUND_H
#define PROJECT_USERNOTFOUND_H

#include <iostream>
#include <exception>
#include <memory>
#include "../../model/user/user.h"

class UserNotFound : public std::invalid_argument{
public:
    UserNotFound(std::shared_ptr<User> user, const std::string & message);
    [[nodiscard]] const std::shared_ptr<User> &getUser() const;

private:
    std::shared_ptr<User> user;

};


#endif //PROJECT_USERNOTFOUND_H
