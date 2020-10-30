//
// Created by biromiro on 27/10/20.
//

#include "viewer_manager.h"

ViewerManager::ViewerManager(UserManager *userManager) {

}

bool ViewerManager::add(Viewer *viewer) {
    if (std::find(viewers.begin(),viewers.end(),viewer) == viewers.end()){
        viewers.push_back(viewer);
        return true;
    }else
        return false;
}

bool ViewerManager::remove(Viewer *viewer) {
    auto it = std::find(viewers.begin(),viewers.end(),viewer);
    if (it != viewers.end()) {
        viewers.erase(it);
        return true;
    }else
        return false;
}

bool ViewerManager::has(Viewer *viewer) const {
    return std::find(viewers.begin(),viewers.end(),viewer) != viewers.end();
}

bool ViewerManager::has(std::string nickname) const {
    return std::find_if(viewers.begin(),viewers.end(),
                        [&nickname](User* user){return user->getNickname() == nickname;}) != viewers.end();
}

Viewer *ViewerManager::get(std::string nickname) const {
    auto it = std::find_if(viewers.begin(),viewers.end(),
                           [&nickname](User* user){return user->getNickname() == nickname;});
    if(it != viewers.end()){
        return *it;
    }
    return nullptr;
}

void ViewerManager::write(std::ostream os) const {
}

void ViewerManager::read(std::istream is) {
}

