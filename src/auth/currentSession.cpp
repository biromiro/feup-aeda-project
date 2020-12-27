//
// Created by biromiro on 15/11/20.
//

#include "currentSession.h"


CurrentSession::CurrentSession() : currentUser(nullptr), userManager(nullptr){}

CurrentSession::CurrentSession(std::shared_ptr<UserManager> userManager): userManager(std::move(userManager)), currentUser(nullptr) {}

bool CurrentSession::login(std::string nickname, const std::string& password) {
    auto user = userManager->get(std::move(nickname));

    //checks if there's not one user already logged in and if the credentials match
    if(user != nullptr && user->getPassword() == password){
        if(user->isDeactivated()){
            std::cout << "This account is deactivated. Do you wish to reactivate it? (Press Y to reactivate)";
            _getch_();
            user->reactivateAcc();
            if(user->getUserType() == UserTypes::STREAMER){
                auto streamer = std::dynamic_pointer_cast<Streamer>(user);
                streamer->makeEligibleToBonus();
            }
        }
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

