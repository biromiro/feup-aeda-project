//
// Created by biromiro on 28/10/20.
//

#ifndef PROJECT_LEADERBOARD_MANAGER_H
#define PROJECT_LEADERBOARD_MANAGER_H

#include "../../user/viewer/viewer_manager.h"
#include "../../user/streamer/streamer_manager.h"
#include "leaderboard.h"


/*enum FilterStream{
    MINIMUM_AGE,
    LANGUAGE,
    GENRE,
    VIEWS,
    LIKES,
    DATE,
    PRIVATE_STREAM,
    PUBLIC_STREAM,
    ACTIVE_STREAM,
    FINISHED_STREAM
};*/

class LeaderboardManager{
public:
    LeaderboardManager(ViewerManager* viewerManager,StreamerManager* streamerManager,StreamManager* streamManager);
    Leaderboard<std::shared_ptr<Stream>> filterStreamByLanguage(StreamLanguage lang);
    Leaderboard<std::shared_ptr<Stream>> filterStreamByAge(unsigned int minAge);
    Leaderboard<std::shared_ptr<Stream>> filterStreamByDate(const Date &date);
    Leaderboard<std::shared_ptr<Stream>> filterStreamByType(StreamType type);
    Leaderboard<std::shared_ptr<Streamer>> sortStreamersByNickname();

private:
    ViewerManager* viewerManager;
    StreamerManager* streamerManager;
    StreamManager* streamManager;



};

#endif //PROJECT_LEADERBOARD_MANAGER_H
