//
// Created by Danny on 25/10/2020.
//

#ifndef PROJECT_STREAMMANAGER_H
#define PROJECT_STREAMMANAGER_H

#include "../user/viewer/viewer_manager.h"
#include "../stream/privateStream/privateStream.h"
#include "../stream/publicStream/publicStream.h"
#include "../stream/finishedStream.h"

class StreamManager{
public:
    StreamManager(ViewerManager* viewerManager);
    void build(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamType type);
    bool add(Stream* streamToAdd);
    bool remove(Stream* streamToRemove);
    bool has(Stream* streamToCheck);
    //bool has(Streamer* streamerToCheck);
    Stream* get(Streamer* streamer);
    bool finish(Stream* streamToFinish);

private:
    ViewerManager* viewerManager;
    std::vector<Stream*> streams;
};

#endif //PROJECT_STREAMMANAGER_H
