//
// Created by biromiro on 27/10/20.
//

#include "viewer_manager.h"
#include "../../../exception/nicknameAlreadyAdded/nicknameAlreadyAdded.h"
#include "../../../exception/userNotFound/userNotFound.h"
#include "../../../exception/userAlreadyExists/userAlreadyExists.h"

ViewerManager::ViewerManager(std::shared_ptr<UserManager> userManager):
userManager(std::move(userManager)){
    viewers = tabHViewer();
}

std::shared_ptr<Viewer> ViewerManager::build(Date birthDate, const std::string& name, const std::string& nickname, const std::string& password) {

    if(userManager->has(nickname))
        throw NicknameAlreadyAdded(nickname,"Nickname already in use by another user!");
    std::shared_ptr<Viewer> viewer;

    //same as streamer, to avoid the creation of an unused Viewer, catches the exception if it is under age,
    //and rethrows it, after reseting its pointer
    try{
        viewer = std::make_shared<Viewer>(birthDate,name,nickname,password);
    } catch (InvalidAge& invalidAge) {
        viewer.reset();
        throw InvalidAge(invalidAge.getAge(),"You have to be at least 12 years old!");
    }

    add(viewer);
    std::shared_ptr<User> user_form = std::dynamic_pointer_cast<Viewer>(viewer);
    userManager->add(user_form);
    return viewer;
}

bool ViewerManager::add(const std::shared_ptr<Viewer>& viewer) {

    if (viewers.find(viewer) == viewers.end()){
        viewers.insert(viewer);
        return true;
    }
    throw UserAlreadyExists(viewer,"The viewer you're trying to add already exists!");
}

bool ViewerManager::reload(const std::shared_ptr<Viewer>& viewer){

    if(userManager->has(viewer->getNickname())){
        throw NicknameAlreadyAdded(viewer->getNickname(),"Nickname already in use by another user!");
    }else{
        std::shared_ptr<User> user_form = std::dynamic_pointer_cast<User>(viewer);
        userManager->add(user_form);
        return add(viewer);
    }
}

bool ViewerManager::remove(const std::shared_ptr<Viewer>& viewer) {

    if (viewers.find(viewer) != viewers.end()) {
        viewers.erase(viewer);
        userManager->remove(std::dynamic_pointer_cast<User>(viewer));
        return true;
    }
    throw UserNotFound(viewer,"The viewer you're trying to remove does not exist!");
}

bool ViewerManager::has(const std::shared_ptr<Viewer>& viewer) const {
    return viewers.find(viewer) != viewers.end();
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

const tabHViewer &ViewerManager::getViewers() const {
    return viewers;
}

bool ViewerManager::readData(const std::shared_ptr<StreamManager>& streamManager) {
    //write object into the file
    std::ifstream file;
    unsigned int viewersSize = 0;

    file.open("../../src/model/user/viewer/dataViewer.txt");

    if(!file){
        std::cout << "Could not open Viewers file...";
        return false;
    }
    file >> viewersSize;

    while(viewersSize--){
        std::shared_ptr<Viewer> newViewer = std::make_shared<Viewer>();
        newViewer->readData(file, streamManager);
        reload(newViewer);
    }
    file.close();
    return true;
}


bool ViewerManager::writeData() {
    //write object into the file
    std::ofstream file;

    file.open("../../src/model/user/viewer/dataViewer.txt");

    if(!file){
        std::cout << "Could not open Viewers file...";
        return false;
    }

    file << viewers.size() << "\n";

    for(const auto& elem: viewers){
        elem->writeData(file);
    }
    file.close();
    return true;
}
