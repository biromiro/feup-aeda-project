//
// Created by emanu on 19-Nov-20.
//

#include "userNotFound.h"

UserNotFound::UserNotFound(std::shared_ptr<User> user, const std::string &message) : user(std::move(std::move(user))),message(message),std::invalid_argument(message){}

const std::string & UserNotFound::getMessage() {return message;}
