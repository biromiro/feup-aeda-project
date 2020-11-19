//
// Created by biromiro on 27/10/20.
//

#include "admin_manager.h"

#include <utility>


AdminManager::AdminManager(std::shared_ptr<UserManager> userManager) :
userManager(std::move(userManager))
{}

bool AdminManager::build(Date birthDate, const std::string &name, const std::string &nickname, std::string password) {
    if(userManager->has(nickname)|| noInstances > 0)
        return false;
    auto newAdmin = std::make_shared<Admin>(birthDate,name,nickname, password);
    add(newAdmin);
    std::shared_ptr<User> user_form = std::dynamic_pointer_cast<User>(newAdmin);
    userManager->add(user_form);
    return true;
}


bool AdminManager::add(const std::shared_ptr<Admin>& adminToAdd) {
    if ( noInstances == 0){
        noInstances++;
        admin = adminToAdd;
        return true;
    }else
        return false;
}

bool AdminManager::remove() {
    if(admin != nullptr){
        userManager->remove(std::dynamic_pointer_cast<User>(admin));
        admin.reset();
        noInstances--;
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


bool AdminManager::readData() {
    //write object into the file
    std::ifstream file;

    file.open("../../src/model/user/admin/dataAdmin.txt");

    if(!file){
        std::cout << "Could not open Streamers file...";
        return false;
    }
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

    file << noInstances << "\n";
    if(admin != nullptr)
        admin->writeData(file);

    file.close();
}