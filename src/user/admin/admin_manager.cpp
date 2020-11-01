//
// Created by biromiro on 27/10/20.
//

#include "admin_manager.h"

unsigned int AdminManager::noInstances = 0;

AdminManager::AdminManager(UserManager *userManager) :
userManager(userManager)
{}

bool AdminManager::build(Date birthDate, const std::string &name, const std::string &nickname) {
    if(userManager->has(nickname) || noInstances > 0)
        return false;
    auto newAdmin = std::make_shared<Admin>(birthDate,name,nickname);
    add(admin);
    std::shared_ptr<User> user_form = std::dynamic_pointer_cast<Admin>(admin);
    userManager->add(user_form);
    return true;
}


bool AdminManager::add(const std::shared_ptr<Admin>& adminToAdd) {
    if ( noInstances == 0){
        ++noInstances;
        admin = adminToAdd;
        return true;
    }else
        return false;
}

bool AdminManager::remove() {
    if(admin != nullptr){
        admin.reset();
        userManager->remove(std::dynamic_pointer_cast<User>(admin));
        return true;
    }
    return false;
}

bool AdminManager::is(const std::shared_ptr<Admin>& adminToCompare) const {
    return admin == adminToCompare;
}

bool AdminManager::is(const std::string& nickname) const {
    return admin->getNickname() == nickname;
}

std::shared_ptr<Admin> AdminManager::get() const {
    return admin;
}

AdminManager::~AdminManager() {
    --noInstances;
}
