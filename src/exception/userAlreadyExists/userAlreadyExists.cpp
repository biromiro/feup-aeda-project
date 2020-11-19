//
// Created by emanu on 18-Nov-20.
//

#include "userAlreadyExists.h"

UserAlreadyExists::UserAlreadyExists(std::shared_ptr<User> user, const std::string & message):user(std::move(std::move(user))),message(message),std::invalid_argument(message){}

const std::string & UserAlreadyExists::getMessage() {return message;}
