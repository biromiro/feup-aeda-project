//
// Created by emanu on 19-Nov-20.
//

#include "userNotFound.h"

UserNotFound::UserNotFound(std::shared_ptr<User> user, const std::string &message) : user(std::move(user)),std::invalid_argument(message){}

const std::shared_ptr<User> &UserNotFound::getUser() const {
    return user;
}
