//
// Created by biromiro on 27/10/20.
//

#include "admin_manager.h"
#include "../../../exception/adminAlreadySet/adminAlreadySet.h"
#include "../../../exception/adminNotSet/adminNotSet.h"
#include "../streamer/streamer.h"


AdminManager::AdminManager(std::shared_ptr<UserManager> userManager) :
userManager(std::move(userManager))
{}

bool AdminManager::build(Date birthDate, const std::string &name, const std::string &nickname, const std::string& password) {

    //there can only be 1 admin at a time
    if(userManager->has(nickname) || noInstances > 0)
        throw AdminAlreadySet(admin,"Admin already set!");

    auto newAdmin = std::make_shared<Admin>(birthDate,name,nickname, password);
    add(newAdmin);
    std::shared_ptr<User> user_form = std::dynamic_pointer_cast<User>(newAdmin);
    userManager->add(user_form);

    return true;
}


bool AdminManager::add(const std::shared_ptr<Admin>& adminToAdd) {

    //same as above, there can only be one instance of Admin
    if ( noInstances == 0){
        noInstances++;
        admin = adminToAdd;
        return true;
    }
    throw AdminAlreadySet(admin,"Admin already set!");
}

bool AdminManager::remove() {

    //checks if the admin is already set
    if(admin != nullptr){
        userManager->remove(std::dynamic_pointer_cast<User>(admin));
        admin.reset();
        noInstances--;
        return true;
    }
    throw AdminNotSet(admin,"Admin not set, can't remove!");
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

unsigned int AdminManager::getMerchLimit() const {
    return merchLimit;
}

void AdminManager::setMerchLimit(unsigned int newLimit) {
    merchLimit = newLimit;
    for(const auto& elem: userManager->getUsers()){
        if (elem->getUserType() == UserTypes::STREAMER) {
            auto item = std::dynamic_pointer_cast<Streamer>(elem);
            if (item->getMerchSetUp()) {
                item->updateMerchLimit(merchLimit);
            }
        }
    }
}

bool AdminManager::readData() {
    //write object into the file
    std::ifstream file;

    file.open("../../src/model/user/admin/dataAdmin.txt");

    if(!file){
        std::cout << "Could not open Streamers file...";
        return false;
    }
    file >> merchLimit;

    file >> noInstances;

    admin = std::make_shared<Admin>();
    admin->readData(file);
    std::shared_ptr<User> user_form = std::dynamic_pointer_cast<User>(admin);
    userManager->add(user_form);
    file.close();
    return true;
}


bool AdminManager::writeData() {
    //write object into the file
    std::ofstream file;

    file.open("../../src/model/user/admin/dataAdmin.txt");

    if(!file){
        std::cout << "Could not open Admin file...";
        return false;
    }

    file << merchLimit << "\n";

    file << noInstances << "\n";
    if(admin != nullptr)
        admin->writeData(file);

    file.close();
    return true;
}