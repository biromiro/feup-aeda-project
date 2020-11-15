//
// Created by biromiro on 15/11/20.
//

#include "currentSession.h"

#include <utility>

CurrentSession::CurrentSession() : currentUser(nullptr), userManager(nullptr){}

CurrentSession::CurrentSession(std::shared_ptr<UserManager> userManager): userManager(std::move(userManager)), currentUser(nullptr) {}

bool CurrentSession::login(std::string nickname, std::string password) {
    auto user = userManager->get(std::move(nickname));
    if(user != nullptr && user->getPassword() == std::move(password)){
        currentUser = user;
        return true;
    }
    return false;
}

bool CurrentSession::logout() {
    if(currentUser != nullptr){
        currentUser = nullptr;
        return true;
    }
    return false;
}

