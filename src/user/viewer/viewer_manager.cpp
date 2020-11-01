//
// Created by biromiro on 27/10/20.
//

#include "viewer_manager.h"

ViewerManager::ViewerManager(UserManager *userManager):
userManager(userManager){}

bool ViewerManager::build(Date birthDate, const std::string& name, const std::string& nickname) {
    if(userManager->has(nickname))
        return false;
    auto viewer = std::make_shared<Viewer>(birthDate,name,nickname);
    add(viewer);
    std::shared_ptr<User> user_form = std::dynamic_pointer_cast<Viewer>(viewer);
    userManager->add(user_form);
    return true;
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