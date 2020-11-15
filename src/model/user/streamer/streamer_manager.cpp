//
// Created by biromiro on 27/10/20.
//

#include "streamer_manager.h"

#include <utility>

StreamerManager::StreamerManager() {}


StreamerManager::StreamerManager(std::shared_ptr<StreamManager> streamManager, std::shared_ptr<ViewerManager> viewerManager, std::shared_ptr<UserManager> userManager):
streamManager(std::move(streamManager)), viewerManager(std::move(viewerManager)), userManager(std::move(userManager))
{
    streamers = std::vector<std::shared_ptr<Streamer>>();
}

std::shared_ptr<Streamer> StreamerManager::build(Date birthDate, const std::string &name, const std::string &nickname, std::string password) {
    if(userManager->has(nickname))
        return nullptr;
    std::shared_ptr<Streamer> streamer;
    try{
        streamer = std::make_shared<Streamer>(birthDate,name,nickname,password);
    } catch (InvalidAge& invalidAge) {
        std::cout << invalidAge.getMessage();
        streamer.reset();
        return nullptr;
    }
    add(streamer);
    std::shared_ptr<User> user_form = std::dynamic_pointer_cast<User>(streamer);
    userManager->add(user_form);
    return streamer;
}

bool StreamerManager::add(const std::shared_ptr<Streamer>& streamer) {
    if (std::find(streamers.begin(),streamers.end(),streamer) == streamers.end()){
        streamers.push_back(streamer);
        return true;
    }else
        return false;
}

bool StreamerManager::reload(const std::shared_ptr<Streamer>& streamer){
    if(userManager->has(streamer->getNickname())){
        return false;
    }else{
        std::shared_ptr<User> user_form = std::dynamic_pointer_cast<User>(streamer);
        userManager->add(user_form);
        return add(streamer);
    }
}

bool StreamerManager::remove(const std::shared_ptr<Streamer>& streamer) {
    auto it = std::find(streamers.begin(),streamers.end(),streamer);
    if (it != streamers.end()) {
        streamers.erase(it);
        userManager->remove(std::dynamic_pointer_cast<User>(streamer));
        return true;
    }else
        return false;
}

bool StreamerManager::startStream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamType type, enum StreamGenre genre, const std::shared_ptr<Streamer>& streamer) {
    std::shared_ptr<Stream> stream = streamManager->build(std::move(title),lang,minAge,type,genre,streamer);
    streamer->setStream(stream);
    return false;
}

bool StreamerManager::endStream(const std::shared_ptr<Streamer>& streamer) {
    if(streamer->isStreaming()){
        streamManager->finish(streamManager->get(streamer->getCurrentStreamID()));
        streamer->removeStream();
        return true;
    }
    return false;
}

bool StreamerManager::has(const std::shared_ptr<Streamer>& streamer) const {
    return std::find(streamers.begin(),streamers.end(),streamer) != streamers.end();
}

bool StreamerManager::has(std::string nickname) const {
    return std::find_if(streamers.begin(),streamers.end(),
                        [&nickname](const std::shared_ptr<Streamer>& streamer){return streamer->getNickname() == nickname;}) != streamers.end();
}

std::shared_ptr<Streamer> StreamerManager::get(std::string nickname) const {
    auto it = std::find_if(streamers.begin(),streamers.end(),
                           [&nickname](const std::shared_ptr<Streamer>& streamer){return streamer->getNickname() == nickname;});
    if(it != streamers.end()){
        return *it;
    }
    return nullptr;
}

unsigned int StreamerManager::getNumOfFollowers(const std::shared_ptr<Streamer> &streamer) const {
    return std::count_if(streamers.begin(),streamers.end(),[&streamer](const std::shared_ptr<Streamer>& str){return streamer == str;});
}

const std::vector<std::shared_ptr<Streamer>> &StreamerManager::getStreamers() const {
    return streamers;
}

bool StreamerManager::readData() {
    //write object into the file
    std::ifstream file;
    unsigned int streamersSize;

    file.open("../../src/model/user/streamer/dataStreamer.txt");

    if(!file){
        std::cout << "Could not open Streamers file...";
        return false;
    }
    file >> streamersSize;

    while(streamersSize--){
        std::shared_ptr<Streamer> newStreamer = std::make_shared<Streamer>();
        newStreamer->readData(file);
        reload(newStreamer);
    }
    file.close();
    return true;
}


bool StreamerManager::writeData() {
    //write object into the file
    std::ofstream file;

    file.open("../../src/model/user/streamer/dataStreamer.txt");

    if(!file){
        std::cout << "Could not open Streamers file...";
        return false;
    }

    file << streamers.size() << "\n";

    for(const auto& elem: streamers){
        elem->writeData(file);
    }
    file.close();
}


