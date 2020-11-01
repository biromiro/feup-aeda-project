//
// Created by biromiro on 27/10/20.
//

#include "streamer_manager.h"

StreamerManager::StreamerManager(StreamManager *streamManager, ViewerManager *viewerManager, UserManager *userManager):
streamManager(streamManager), viewerManager(viewerManager), userManager(userManager)
{
    streamers = std::vector<std::shared_ptr<Streamer>>();
}

bool StreamerManager::build(Date birthDate, const std::string &name, const std::string &nickname) {
    if(userManager->has(nickname))
        return false;
    auto streamer = std::make_shared<Streamer>(birthDate,name,nickname);
    add(streamer);
    std::shared_ptr<User> user_form = std::dynamic_pointer_cast<Streamer>(streamer);
    userManager->add(user_form);
    return true;
}

bool StreamerManager::add(const std::shared_ptr<Streamer>& streamer) {
    if (std::find(streamers.begin(),streamers.end(),streamer) == streamers.end()){
        streamers.push_back(streamer);
        return true;
    }else
        return false;
}

bool StreamerManager::remove(const std::shared_ptr<Streamer>& streamer) {
    auto it = std::find(streamers.begin(),streamers.end(),streamer);
    if (it != streamers.end()) {
        streamers.erase(it);
        return true;
    }else
        return false;
}

bool StreamerManager::startStream(const std::shared_ptr<Streamer>& streamer, std::string title, StreamLanguage lang, unsigned int minAge,
                                  StreamType type) {
    //Stream* stream = streamManager->build(title,lang,minAge,type);
    //streamer->setStream(stream);
    return false;
}

bool StreamerManager::endStream(const std::shared_ptr<Streamer>& streamer) {
    if(streamer->isStreaming()){
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



