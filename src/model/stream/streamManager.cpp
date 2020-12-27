//
// Created by Danny on 25/10/2020.
//

#include "streamManager.h"
#include "../../exception/streamerAlreadyStreaming/streamerAlreadyStreaming.h"
#include "../../exception/invalidStreamBuild/invalidStreamBuild.h"
#include "../../exception/invalidStreamAdd/invalidStreamToAdd.h"
#include "../../exception/streamNotFound/streamNotFound.h"
#include "../../exception/noStreamWithID/noStreamWithID.h"
#include "../../exception/streamAlreadyFinished/streamAlreadyFinished.h"

StreamManager::StreamManager(std::shared_ptr<ViewerManager> viewerManager, std::shared_ptr<StreamerManager> streamerManager) :
viewerManager(std::move(viewerManager)), streamerManager(std::move(streamerManager)) {}

std::shared_ptr<Stream> StreamManager::build(const std::string& title, enum StreamLanguage lang, unsigned int minAge, enum StreamType type, enum StreamGenre genre, const std::shared_ptr<Streamer>& streamer){

    //a streamer can only stream 1 stream at a time
    if(streamer->isStreaming())
        throw StreamerAlreadyStreaming(streamer, "Streamer is already streaming right now!");

    //depending on the type of build, makes a different pointer (either to PrivateStream or to PublicStream)
    switch(type) {

        case StreamType::PRIVATE: {

            auto prv_stream = std::make_shared<PrivateStream>(title, lang, minAge, genre, streamer);
            auto stream_form = std::dynamic_pointer_cast<Stream>(prv_stream);
            add(stream_form);
            streamer->setStream(stream_form);
            if(streamer->ellegibleForBonus()){
                stream_form->reactivationBonus();
                streamer->useBonus();
            }
            return stream_form;

        }

        case StreamType::PUBLIC: {

            auto pbl_stream = std::make_shared<PublicStream>(title, lang, minAge, genre, streamer);
            auto stream_form = std::dynamic_pointer_cast<Stream>(pbl_stream);
            add(stream_form);
            streamer->setStream(stream_form);
            if(streamer->ellegibleForBonus()){
                stream_form->reactivationBonus();
                streamer->useBonus();
            }
            return stream_form;

        }

        default:
            throw InvalidStreamBuild("The stream you're trying to start is invalid!");
    }
}

bool StreamManager::add(const std::shared_ptr<Stream>& streamToAdd) {

    //checks if the stream to add is in the cache of finished streams if it is of that type
    if (streamToAdd->getStreamType() == StreamType::FINISHED &&
    (std::find(cacheOfFinishedStreams.begin(), cacheOfFinishedStreams.end(), streamToAdd) == cacheOfFinishedStreams.end())){
        cacheOfFinishedStreams.push_back(streamToAdd);
        return true;
    }

    //checks if it is in the live stream vector
    else if (std::find(streams.begin(), streams.end(), streamToAdd) == streams.end()
    && streamToAdd->getStreamType() != StreamType::FINISHED){
        streams.push_back(streamToAdd);
        return true;
    }

    throw InvalidStreamToAdd(streamToAdd, "Stream you're trying to add is invalid or already there!");
}

bool StreamManager::remove(const std::shared_ptr<Stream>& streamToRemove) {

    //checks if the stream is in the vector in order to be removed
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

    //searches for the stream given its streamID in both the cache and stream vectors
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

    //a finished stream cannot be finished
    if(streamToFinish->getStreamType() == StreamType::FINISHED)
        throw StreamAlreadyFinished(streamToFinish, "Stream has already finished!");

    //if the stream isn't in the stream vector, it cannot be finished
    if(!remove(streamToFinish)) return nullptr;

    //creates a new finished stream object
    auto res = std::make_shared<FinishedStream>(streamToFinish->getTitle(),streamToFinish->getLanguage(), streamToFinish->getMinAge(),
                                                streamToFinish->getGenre(), streamToFinish->getStreamer(), getNumOfViewers(streamToFinish), streamToFinish->getUniqueId(), streamToFinish->getVotes());

    //leaves the stream for each viewer actually watching the stream
    for(const auto& elem: viewerManager->getViewers()){
        if(elem->getCurrentStream() == streamToFinish)
            elem->leaveCurrentStream();

        //changes the pointer of the viewerStreamHistory feedback to the new finished stream one
        std::map<std::shared_ptr<Stream>,FeedbackLikeSystem>& viewerStreamHistory = elem->getStreamHistory();
        auto it = viewerStreamHistory.find(streamToFinish);
        if(it != viewerStreamHistory.end()){
            FeedbackLikeSystem vote = (*it).second;
            viewerStreamHistory.erase(it);
            viewerStreamHistory.insert(std::pair<std::shared_ptr<Stream>,FeedbackLikeSystem>(res,vote));
        }

    }
    cacheOfFinishedStreams.push_back(res);
    streamToFinish->getStreamer()->addToViewCount(streamToFinish->getNumOfViewers());

    return res;
}

unsigned int StreamManager::getNumOfViewers(const std::shared_ptr<Stream> &streamToFinish) {
    return static_cast<unsigned int>(std::count_if(viewerManager->getViewers().begin(),
                                                   viewerManager->getViewers().end(),
                                                   [&streamToFinish](const std::shared_ptr<Viewer> &v) {
                                                       return v->getCurrentStream() == streamToFinish;
                                                   }));
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

    unsigned int streamsSize = 0, cacheOfFinishedStreamsSize = 0;

    StreamType type = StreamType::PUBLIC;

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
    return true;
}

void StreamManager::setStreamerManager(std::shared_ptr<StreamerManager> newStreamerManager) {
    streamerManager = std::move(newStreamerManager);
}
