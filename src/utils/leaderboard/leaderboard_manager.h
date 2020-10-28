//
// Created by biromiro on 28/10/20.
//

#ifndef PROJECT_LEADERBOARD_MANAGER_H
#define PROJECT_LEADERBOARD_MANAGER_H

#include "../../user/viewer/viewer_manager.h"
#include "../../user/streamer/streamer_manager.h"


class LeaderboardManager{
public:
    LeaderboardManager(ViewerManager* viewerManager,StreamerManager* streamerManager,StreamManager* streamManager);

private:
    ViewerManager* viewerManager;
    StreamerManager* streamerManager;
    StreamManager* streamManager;
};

#endif //PROJECT_LEADERBOARD_MANAGER_H
