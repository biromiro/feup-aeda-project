//
// Created by biromiro on 15/11/20.
//

#ifndef PROJECT_CURRENTSESSION_H
#define PROJECT_CURRENTSESSION_H

#include <iostream>
#include "../model/user/user_manager.h"

class CurrentSession{
private:
    std::shared_ptr<UserManager> userManager;
    std::shared_ptr<User> currentUser;
public:
    CurrentSession();
    explicit CurrentSession(std::shared_ptr<UserManager> userManager);
    bool login(std::string nickname, std::string password);
    bool logout();
};

#endif //PROJECT_CURRENTSESSION_H
