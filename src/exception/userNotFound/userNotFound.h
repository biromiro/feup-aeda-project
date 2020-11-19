//
// Created by emanu on 19-Nov-20.
//

#ifndef STREAMER_MANAGER_TEST_CPP_USERNOTFOUND_H
#define STREAMER_MANAGER_TEST_CPP_USERNOTFOUND_H

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


#endif //STREAMER_MANAGER_TEST_CPP_USERNOTFOUND_H
