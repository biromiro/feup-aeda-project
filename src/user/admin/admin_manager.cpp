//
// Created by biromiro on 27/10/20.
//

#include "admin_manager.h"

unsigned int AdminManager::noInstances = 0;

AdminManager::AdminManager(UserManager *userManager) :
userManager(userManager)
{}

bool AdminManager::add(Admin *adminToAdd) {
    if ( noInstances == 0){
        ++noInstances;
        admin = adminToAdd;
    }else
        throw std::logic_error( "Cannot create another instance" );
}

bool AdminManager::remove(Admin *adminToAdd) {
    if(admin != nullptr){
        admin = nullptr;
        return true;
    }
    return false;
}

bool AdminManager::is(Admin *adminToCompare) const {
    return admin == adminToCompare;
}

bool AdminManager::is(std::string nickname) const {
    return admin->getNickname() == nickname;
}

Admin *AdminManager::get() const {
    return admin;
}

AdminManager::~AdminManager() {
    --noInstances;
}

