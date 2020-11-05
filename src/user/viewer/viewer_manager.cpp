//
// Created by biromiro on 27/10/20.
//

#include "viewer_manager.h"

#include <utility>

ViewerManager::ViewerManager(std::shared_ptr<UserManager> userManager):
userManager(std::move(userManager)){
    viewers = std::vector<std::shared_ptr<Viewer>>();
}

std::shared_ptr<Viewer> ViewerManager::build(Date birthDate, const std::string& name, const std::string& nickname) {
    if(userManager->has(nickname))
        return nullptr;
    auto viewer = std::make_shared<Viewer>(birthDate,name,nickname);
    add(viewer);
    std::shared_ptr<User> user_form = std::dynamic_pointer_cast<Viewer>(viewer);
    userManager->add(user_form);
    return viewer;
}

bool ViewerManager::add(const std::shared_ptr<Viewer>& viewer) {
    if (std::find(viewers.begin(),viewers.end(),viewer) == viewers.end()){
        viewers.push_back(viewer);
        return true;
    }else
        return false;
}

bool ViewerManager::remove(const std::shared_ptr<Viewer>& viewer) {
    auto it = std::find(viewers.begin(),viewers.end(),viewer);
    if (it != viewers.end()) {
        viewers.erase(it);
        userManager->remove(std::dynamic_pointer_cast<User>(viewer));
        return true;
    }else
        return false;
}

bool ViewerManager::has(const std::shared_ptr<Viewer>& viewer) const {
    return std::find(viewers.begin(),viewers.end(),viewer) != viewers.end();
}

bool ViewerManager::has(std::string nickname) const {
    return std::find_if(viewers.begin(),viewers.end(),
                        [&nickname](const std::shared_ptr<Viewer>& viewer){return viewer->getNickname() == nickname;}) != viewers.end();
}

std::shared_ptr<Viewer> ViewerManager::get(std::string nickname) const {
    auto it = std::find_if(viewers.begin(),viewers.end(),
                           [&nickname](const std::shared_ptr<Viewer>& viewer){return viewer->getNickname() == nickname;});
    if(it != viewers.end()){
        return *it;
    }
    return nullptr;
}

const std::vector<std::shared_ptr<Viewer>> &ViewerManager::getViewers() const {
    return viewers;
}

bool ViewerManager::readData() {
    //open file again
    std::fstream file;

    file.open("../../src/user/viewer/dataViewer.dat",std::ios::in|std::ios::binary);
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


bool ViewerManager::writeData() {
    //write object into the file
    std::fstream file;

    file.open("../../src/user/viewer/dataViewer.dat",std::ios::out|std::ios::binary);
    if(!file){
        std::cout<<"Could not save the current session...\n";
        return false;
    }

    file.write((char*)this,sizeof(*this));
    file.close();
    std::cout<<"Date saved into file the file.\n";
    return true;
}
