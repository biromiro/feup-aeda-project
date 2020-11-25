//
// Created by biromiro on 27/10/20.
//

#include <algorithm>
#include "../../exception/userAlreadyExists/userAlreadyExists.h"
#include "../../exception/userNotFound/userNotFound.h"
#include "user_manager.h"

UserManager::UserManager() {
    users = std::unordered_set<std::shared_ptr<User>>();
}

bool UserManager::add(const std::shared_ptr<User>& user) {
    if (users.find(user) == users.end()){
        users.insert(user);
        return true;
    }
    throw UserAlreadyExists(user,"The user you're trying to add already exists!");
}

bool UserManager::remove(const std::shared_ptr<User>& user) {
    if (users.find(user) != users.end()) {
        users.erase(user);
        return true;
    }
    throw UserNotFound(user,"The user you're looking for does not exist!");
}

bool UserManager::has(const std::shared_ptr<User>& user) const {
    return users.find(user) != users.end();
}

bool UserManager::has(std::string nickname) const {
    return std::find_if(users.begin(),users.end(),
                        [&nickname](const std::shared_ptr<User>& user){return user->getNickname() == nickname;}) != users.end();
}

std::shared_ptr<User> UserManager::get(std::string nickname) const {
    auto it = std::find_if(users.begin(),users.end(),
                           [&nickname](const std::shared_ptr<User>& user){return user->getNickname() == nickname;});

    if(it != users.end()){
        return *it;
    }

    return nullptr;
}

std::unordered_set<std::shared_ptr<User>> UserManager::getUsers() const {
    return users;
}

