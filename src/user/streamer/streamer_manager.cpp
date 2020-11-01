//
// Created by biromiro on 27/10/20.
//

#include "streamer_manager.h"

StreamerManager::StreamerManager(StreamManager *streamManager, ViewerManager *viewerManager, UserManager *userManager):
streamManager(streamManager), viewerManager(viewerManager), userManager(userManager)
{
    streamers = std::vector<Streamer*>();
}

bool StreamerManager::add(Streamer *streamer) {
    if (std::find(streamers.begin(),streamers.end(),streamer) == streamers.end()){
        streamers.push_back(streamer);
        return true;
    }else
        return false;
}

bool StreamerManager::remove(Streamer *streamer) {
    auto it = std::find(streamers.begin(),streamers.end(),streamer);
    if (it != streamers.end()) {
        streamers.erase(it);
        return true;
    }else
        return false;
}

bool StreamerManager::startStream(Streamer *streamer, std::string title, StreamLanguage lang, unsigned int minAge,
                                  StreamType type) {
    //Stream* stream = streamManager->build(title,lang,minAge,type);
    //streamer->setStream(stream);
    return false;
}

bool StreamerManager::endStream(Streamer *streamer) {
    if(streamer->isStreaming()){
        streamer->removeStream();
        return true;
    }
    return false;
}

bool StreamerManager::has(Streamer *streamer) const {
    return std::find(streamers.begin(),streamers.end(),streamer) != streamers.end();
}

bool StreamerManager::has(std::string nickname) const {
    return std::find_if(streamers.begin(),streamers.end(),
                        [&nickname](User* user){return user->getNickname() == nickname;}) != streamers.end();
}

Streamer *StreamerManager::get(std::string nickname) const {
    auto it = std::find_if(streamers.begin(),streamers.end(),
                           [&nickname](User* user){return user->getNickname() == nickname;});
    if(it != streamers.end()){
        return *it;
    }
    return nullptr;
}



