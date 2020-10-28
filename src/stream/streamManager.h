//
// Created by Danny on 25/10/2020.
//

#ifndef PROJECT_STREAMMANAGER_H
#define PROJECT_STREAMMANAGER_H

#include "../user/viewer/viewer_manager.h"

class StreamManager{
public:
    StreamManager(ViewerManager* viewerManager);

private:
    ViewerManager* viewerManager;
};

#endif //PROJECT_STREAMMANAGER_H
