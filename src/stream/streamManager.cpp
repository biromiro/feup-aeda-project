//
// Created by Danny on 25/10/2020.
//

#include "streamManager.h"

StreamManager::StreamManager(ViewerManager *viewerManager) {

}

void StreamManager::build(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamType type){

}

bool StreamManager::add(Stream* streamToAdd) {
    streams.push_back(streamToAdd);
    return true;
}