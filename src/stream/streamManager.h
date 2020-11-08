//
// Created by Danny on 25/10/2020.
//

#ifndef PROJECT_STREAMMANAGER_H
#define PROJECT_STREAMMANAGER_H

#include "../user/viewer/viewer_manager.h"
#include "../stream/privateStream/privateStream.h"
#include "../stream/publicStream/publicStream.h"
#include "../stream/finishedStream/finishedStream.h"
#include "../user/streamer/streamer.h"
#include <memory>

class StreamManager{
public:
    StreamManager(std::shared_ptr<ViewerManager> viewerManager, std::shared_ptr<StreamerManager> streamerManager);
    std::shared_ptr<Stream> build(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamType type, enum StreamGenre genre, std::shared_ptr<Streamer> streamer);
    bool add(std::shared_ptr<Stream> streamToAdd);
    bool remove(std::shared_ptr<Stream> streamToRemove);
    bool has(const std::shared_ptr<Stream>& streamToCheck);
    std::shared_ptr<Stream> get(unsigned int streamID);
    bool finish(const std::shared_ptr<Stream>& streamToFinish);
    unsigned int getNumOfViewers(const std::shared_ptr<Stream>& streamToFinish);
    void setStreamerManager(std::shared_ptr<StreamerManager> newStreamerManager);
    const std::vector<std::shared_ptr<Stream>> &getStreams() const;
    const std::vector<std::shared_ptr<Stream>> &getCacheOfFinishedStreams() const;

    bool readData();

    bool writeData();

private:
    std::shared_ptr<StreamerManager> streamerManager;
    std::shared_ptr<ViewerManager> viewerManager;
    std::vector<std::shared_ptr<Stream>> streams;
    std::vector<std::shared_ptr<Stream>> cacheOfFinishedStreams;
};

#endif //PROJECT_STREAMMANAGER_H
