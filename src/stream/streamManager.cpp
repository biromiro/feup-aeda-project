//
// Created by Danny on 25/10/2020.
//

#include "streamManager.h"
#include <memory>

StreamManager::StreamManager(ViewerManager *viewerManager) {

}

void StreamManager::build(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamType type){
    /*
    switch(type) {
        case PRIVATE:
            std::shared_ptr<PrivateStream> prv_stream = std::make_shared<PrivateStream>(title, lang, minAge);
            break;
        case PUBLIC:
            std::shared_ptr<PublicStream> pbl_stream = std::make_shared<PublicStream>(title, lang, minAge);
            break;
        default:
            break;
    } */
}

bool StreamManager::add(Stream* streamToAdd) {
    streams.push_back(streamToAdd);
    return true;
}

bool StreamManager::remove(Stream* streamToRemove) {
    std::vector<Stream*>::iterator itr;
    for (itr = streams.begin(); itr != streams.end(); itr++) {
        if ((*itr)->getTitle() == streamToRemove->getTitle()){
            streams.erase(itr);
            return true;
        }
    } // pode dar erro na comparação qnd a stream n estiver por causa do itr.end()
    std::cout << "Stream not found! " << std::endl;
    return false;
}

bool StreamManager::has(Stream* streamToCheck) {
    std::vector<Stream*>::iterator itr;
    for (itr = streams.begin(); itr != streams.end(); itr++) {
        if ((*itr)->getTitle() == streamToCheck->getTitle()) {
            return true;
        }
    }
    return false;
}

Stream* StreamManager::get(Streamer* streamer) {
    for (unsigned int i = 0; i < streams.size(); i++) {
        if (streams[i]->getStreamer() == streamer) {
            return streams[i];
        }
    }
}

bool StreamManager::finish(Stream* streamToFinish) { //e se for public ou private?
    unsigned int finalViews = streamToFinish->getViewerCount();
    FinishedStream res = FinishedStream(finalViews); //criar como shared pointer?
    return true;
}


