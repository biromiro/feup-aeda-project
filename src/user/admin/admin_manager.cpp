//
// Created by biromiro on 27/10/20.
//

#include "admin_manager.h"

#include <utility>


AdminManager::AdminManager(std::shared_ptr<UserManager> userManager) :
userManager(std::move(userManager))
{}

bool AdminManager::build(Date birthDate, const std::string &name, const std::string &nickname) {
    if(userManager->has(nickname)|| noInstances > 0)
        return false;
    auto newAdmin = std::make_shared<Admin>(birthDate,name,nickname);
    add(newAdmin);
    std::shared_ptr<User> user_form = std::dynamic_pointer_cast<Admin>(newAdmin);
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
        admin.reset();
        userManager->remove(std::dynamic_pointer_cast<User>(admin));
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
    //open file again
    std::fstream file;

    file.open("../../src/user/admin/dataAdmin.dat",std::ios::in|std::ios::binary);
    if(!file){
        std::cout << "Error in opening file..." << std::endl;
        return false;
    }

    if(!file.read((char*)this,sizeof(*this))){
        std::cout << "Could not fetch the last session's data..." << std::endl;
        return -1;
    }

    file.close();
    return true;
}


bool AdminManager::writeData() {
    //write object into the file
    std::fstream file;

    file.open("../../src/user/admin/dataAdmin.dat",std::ios::out|std::ios::binary);
    if(!file){
        std::cout<<"Could not save the current session...\n";
        return false;
    }

    file.write((char*)this,sizeof(*this));
    file.close();
    std::cout<<"Date saved into file the file.\n";
    return true;
}