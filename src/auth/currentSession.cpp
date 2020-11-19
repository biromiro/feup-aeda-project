//
// Created by biromiro on 15/11/20.
//

#include "currentSession.h"

CurrentSession::CurrentSession() : currentUser(nullptr), userManager(nullptr){}

CurrentSession::CurrentSession(std::shared_ptr<UserManager> userManager): userManager(std::move(userManager)), currentUser(nullptr) {}

bool CurrentSession::login(std::string nickname, const std::string& password) {
    auto user = userManager->get(std::move(nickname));
    if(user != nullptr && user->getPassword() == password){
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

std::string CurrentSession::getNickname() const {
    return currentUser->getNickname();
}

const std::shared_ptr<User> &CurrentSession::getCurrentUser() const {
    return currentUser;
}

