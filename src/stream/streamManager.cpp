//
// Created by Danny on 25/10/2020.
//

#include "streamManager.h"

StreamManager::StreamManager(ViewerManager *viewerManager) : viewerManager(viewerManager) {}

std::shared_ptr<Stream> StreamManager::build(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamType type, std::shared_ptr<Streamer> streamer){
    switch(type) {
        case PRIVATE: {
            auto prv_stream = std::make_shared<PrivateStream>(title, lang, minAge, streamer);
            auto stream_form = std::dynamic_pointer_cast<Stream>(prv_stream);
            add(stream_form);
            streamer->setStream(stream_form);
            return stream_form;
        }
        case PUBLIC: {
            auto pbl_stream = std::make_shared<PublicStream>(title, lang, minAge, streamer);
            auto stream_form = std::dynamic_pointer_cast<Stream>(pbl_stream);
            add(stream_form);
            streamer->setStream(stream_form);
            return stream_form;
        }
        default:
            return nullptr;
    }
} // mudar para bool?

bool StreamManager::add(std::shared_ptr<Stream> streamToAdd) {
    if (std::find(streams.begin(), streams.end(), streamToAdd) == streams.end()){
        streams.push_back(streamToAdd);
        return true;
    }
    return false;
}

bool StreamManager::remove(std::shared_ptr<Stream> streamToRemove) {
    auto itr = std::find(streams.begin(), streams.end(), streamToRemove);
    if (itr != streams.end()) {
        streams.erase(itr);
        return true;
    }
    return false;
}

bool StreamManager::has(std::shared_ptr<Stream> streamToCheck) {
    return std::find(streams.begin(), streams.end(), streamToCheck) != streams.end();
}

std::shared_ptr<Stream> StreamManager::get(std::shared_ptr<Streamer> streamer) {
    auto itr = std::find_if(streams.begin(), streams.end(),
                           [&streamer](const std::shared_ptr<Stream>& stream){return stream->getStreamer() == streamer;});
    if(itr != streams.end()){
        return *itr;
    }
    return nullptr;
}

bool StreamManager::finish(std::shared_ptr<Stream> streamToFinish) {
    auto res = std::dynamic_pointer_cast<FinishedStream>(streamToFinish);
    return true;
}

const std::vector<std::shared_ptr<Stream>> &StreamManager::getStreams() const {
    return streams;
}

const std::vector<std::shared_ptr<Stream>> &StreamManager::getCacheOfFinishedStreams() const {
    return cacheOfFinishedStreams;
}


