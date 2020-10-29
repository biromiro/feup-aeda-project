//
// Created by Danny on 25/10/2020.
//

#ifndef PROJECT_STREAMMANAGER_H
#define PROJECT_STREAMMANAGER_H

#include "../user/viewer/viewer_manager.h"

class StreamManager{
public:
    StreamManager(ViewerManager* viewerManager);
    void build(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamType type);
    bool add(Stream* streamToAdd);

private:
    ViewerManager* viewerManager;
    std::vector<Stream*> streams;
};

#endif //PROJECT_STREAMMANAGER_H
