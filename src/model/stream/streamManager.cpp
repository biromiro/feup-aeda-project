//
// Created by Danny on 25/10/2020.
//

#include "streamManager.h"
#include "../../exception/streamNotFound.cpp"
#include "../../exception/noStreamWithID.cpp"
#include "../../exception/invalidStreamToAdd.cpp"
#include "../../exception/streamAlreadyFinished.cpp"

#include <utility>

StreamManager::StreamManager(std::shared_ptr<ViewerManager> viewerManager, std::shared_ptr<StreamerManager> streamerManager) :
viewerManager(std::move(viewerManager)), streamerManager(std::move(streamerManager)) {}

std::shared_ptr<Stream> StreamManager::build(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamType type, enum StreamGenre genre, std::shared_ptr<Streamer> streamer){
    if(streamer->isStreaming())
        return nullptr;
    switch(type) {
        case StreamType::PRIVATE: {
            auto prv_stream = std::make_shared<PrivateStream>(title, lang, minAge, genre, streamer);
            auto stream_form = std::dynamic_pointer_cast<Stream>(prv_stream);
            add(stream_form);
            streamer->setStream(stream_form);
            return stream_form;
        }
        case StreamType::PUBLIC: {
            auto pbl_stream = std::make_shared<PublicStream>(title, lang, minAge, genre, streamer);
            auto stream_form = std::dynamic_pointer_cast<Stream>(pbl_stream);
            add(stream_form);
            streamer->setStream(stream_form);
            return stream_form;
        }
        default:
            return nullptr;
    }
}

bool StreamManager::add(std::shared_ptr<Stream> streamToAdd) {
    if ((std::find(cacheOfFinishedStreams.begin(), cacheOfFinishedStreams.end(), streamToAdd) == cacheOfFinishedStreams.end())
    && streamToAdd->getStreamType() == StreamType::FINISHED){
        cacheOfFinishedStreams.push_back(streamToAdd);
        return true;
    }
    else if (std::find(streams.begin(), streams.end(), streamToAdd) == streams.end()
    && streamToAdd->getStreamType() != StreamType::FINISHED){
        streams.push_back(streamToAdd);
        return true;
    }
    throw InvalidStreamToAdd(streamToAdd, "Stream you're trying to add is invalid or already there!");
}

bool StreamManager::remove(std::shared_ptr<Stream> streamToRemove) {
    auto itr = std::find(streams.begin(), streams.end(), streamToRemove);
    if (itr != streams.end()) {
        streams.erase(itr);
        return true;
    }
    throw StreamNotFound(streamToRemove, "Stream not found!");
}

bool StreamManager::has(const std::shared_ptr<Stream>& streamToCheck) {
    return std::find(streams.begin(), streams.end(), streamToCheck) != streams.end();
}

std::shared_ptr<Stream> StreamManager::get(unsigned int streamID) {
    auto itr = std::find_if(streams.begin(), streams.end(),
                           [streamID](const std::shared_ptr<Stream>& stream){return stream->getUniqueId() == streamID;});
    if(itr != streams.end()){
        return *itr;
    }
    itr = std::find_if(cacheOfFinishedStreams.begin(), cacheOfFinishedStreams.end(),
                            [streamID](const std::shared_ptr<Stream>& stream){return stream->getUniqueId() == streamID;});
    if(itr != cacheOfFinishedStreams.end()){
        return *itr;
    }
    throw NoStreamWithID(streamID, "There's no stream with that ID!");
}

std::shared_ptr<FinishedStream> StreamManager::finish(const std::shared_ptr<Stream>& streamToFinish) {
    if(streamToFinish->getStreamType() == StreamType::FINISHED)
        throw StreamAlreadyFinished(streamToFinish, "Stream has already finished!");
    if(!remove(streamToFinish)) return nullptr;
    auto res = std::make_shared<FinishedStream>(streamToFinish->getTitle(),streamToFinish->getLanguage(), streamToFinish->getMinAge(),
                                                streamToFinish->getGenre(), streamToFinish->getStreamer(), getNumOfViewers(streamToFinish), streamToFinish->getUniqueId());
    for(const auto& elem: viewerManager->getViewers()){
        if(elem->getCurrentStream() == streamToFinish)
            elem->leaveCurrentStream();
    }
    cacheOfFinishedStreams.push_back(res);
    return res;
}

unsigned int StreamManager::getNumOfViewers(const std::shared_ptr<Stream> &streamToFinish) {
    return std::count_if(viewerManager->getViewers().begin(),viewerManager->getViewers().end(),[&streamToFinish](const std::shared_ptr<Viewer>& v){return v->getCurrentStream()==streamToFinish;});
}

const std::vector<std::shared_ptr<Stream>> &StreamManager::getStreams() const {
    return streams;
}

const std::vector<std::shared_ptr<Stream>> &StreamManager::getCacheOfFinishedStreams() const {
    return cacheOfFinishedStreams;
}


bool StreamManager::readData() {
    //open file again
    std::ifstream file;

    unsigned int streamsSize, cacheOfFinishedStreamsSize;

    StreamType type;

    file.open("../../src/model/stream/dataStream.txt");
    if(!file){
        std::cout << "Error in opening file..." << std::endl;
        return false;
    }

    file >> streamsSize;
    file.ignore();

    while (streamsSize--){
        file >> type;
        switch (type) {
            case StreamType::PUBLIC: {
                std::shared_ptr<PublicStream> newPublicStream = std::make_shared<PublicStream>();
                newPublicStream->readData(file, streamerManager);
                add(newPublicStream);
                break;
            }
            case StreamType::PRIVATE: {
                std::shared_ptr<PrivateStream> newPrivateStream = std::make_shared<PrivateStream>();
                newPrivateStream->readData(file, streamerManager);
                add(newPrivateStream);
            }
        }
    }

    file >> cacheOfFinishedStreamsSize;

    while (cacheOfFinishedStreamsSize--){
        std::shared_ptr<FinishedStream> finishedStream = std::make_shared<FinishedStream>();
        finishedStream->readData(file, streamerManager);
        add(finishedStream);
    }
    file.close();
    return true;
}


bool StreamManager::writeData() {
    //write object into the file
    std::ofstream file;

    file.open("../../src/model/stream/dataStream.txt");

    if (!file) {
        std::cout << "Could not open Streamers file...";
        return false;
    }

    file << streams.size() << "\n";

    for (const auto &elem: streams) {
        switch (elem->getStreamType()) {
            case StreamType::PRIVATE:{
                file << "PRIVATE" << "\n";
                auto privateStream = std::dynamic_pointer_cast<PrivateStream>(elem);
                privateStream->writeData(file);
                break;
            }
            case StreamType::PUBLIC: {
                file << "PUBLIC" << "\n";
                auto publicStream = std::dynamic_pointer_cast<PublicStream>(elem);
                publicStream->writeData(file);
                break;
            }
        }
    }

    file << cacheOfFinishedStreams.size() << "\n";

    for (const auto &elem: cacheOfFinishedStreams){
        auto finishedStream = std::dynamic_pointer_cast<FinishedStream>(elem);
        finishedStream->writeData(file);
    }
    file.close();
}

void StreamManager::setStreamerManager(std::shared_ptr<StreamerManager> newStreamerManager) {
    streamerManager = std::move(newStreamerManager);
}
