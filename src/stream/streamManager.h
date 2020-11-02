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
    StreamManager(ViewerManager* viewerManager);
    std::shared_ptr<Stream> build(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamType type, std::shared_ptr<Streamer> streamer);
    bool add(std::shared_ptr<Stream> streamToAdd);
    bool remove(std::shared_ptr<Stream> streamToRemove);
    bool has(std::shared_ptr<Stream> streamToCheck);
    std::shared_ptr<Stream> get(std::shared_ptr<Streamer> streamer);
    bool finish(std::shared_ptr<Stream> streamToFinish);
    const std::vector<std::shared_ptr<Stream>> &getStreams() const;
    const std::vector<std::shared_ptr<Stream>> &getCacheOfFinishedStreams() const;

private:
    ViewerManager* viewerManager;
    std::vector<std::shared_ptr<Stream>> streams;
    std::vector<std::shared_ptr<Stream>> cacheOfFinishedStreams;
};

#endif //PROJECT_STREAMMANAGER_H
