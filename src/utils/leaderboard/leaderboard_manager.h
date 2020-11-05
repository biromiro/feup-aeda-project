//
// Created by biromiro on 28/10/20.
//

#ifndef PROJECT_LEADERBOARD_MANAGER_H
#define PROJECT_LEADERBOARD_MANAGER_H

#include "../../user/viewer/viewer_manager.h"
#include "../../user/streamer/streamer_manager.h"
#include "leaderboard.h"


enum SortStream{
    MINIMUM_AGE,
    LANGUAGE,
    GENRE,
    VIEWS,
    LIKES,
    DATE,
    TYPE
};

enum SortUser{
    NAME,
    NICKNAME,
    BIRTHDATE,
    JOINDATE,
    USERTYPE
};

enum SortViewer{
    NAME_V,
    NICKNAME_V,
    BIRTHDATE_V,
    JOINDATE_V,
    WATCHING_STREAM,
    NUM_OF_WATCHED_STREAMS
};

enum SortStreamer{
    NAME_S,
    NICKNAME_S,
    BIRTHDATE_S,
    JOINDATE_S,
    VIEWCOUNT,
    STREAMING,
    NUM_FOLLOWERS
};

class LeaderboardManager{
public:
    LeaderboardManager(std::shared_ptr<ViewerManager> viewerManager,std::shared_ptr<StreamerManager> streamerManager,std::shared_ptr<StreamManager> streamManager, std::shared_ptr<UserManager> userManager);
    Leaderboard<std::shared_ptr<Stream>> filterStreamByLanguage(StreamLanguage lang);
    Leaderboard<std::shared_ptr<Stream>> filterStreamByGenre(StreamGenre genre);
    Leaderboard<std::shared_ptr<Stream>> filterStreamByAge(unsigned int minAge);
    Leaderboard<std::shared_ptr<Stream>> filterStreamByStreamer(const std::string& nickname);
    Leaderboard<std::shared_ptr<Stream>> filterStreamByDate(const Date &date);
    Leaderboard<std::shared_ptr<Stream>> filterStreamByType(StreamType type);
    Leaderboard<std::shared_ptr<Streamer>> sortStreamers();
    Leaderboard<std::shared_ptr<Streamer>> sortStreamers(const Leaderboard<std::shared_ptr<Streamer>>& lb);
    Leaderboard<std::shared_ptr<Streamer>> sortStreamerBy(SortStreamer sorter);
    Leaderboard<std::shared_ptr<Viewer>> sortViewers();
    Leaderboard<std::shared_ptr<Viewer>> sortViewers(const Leaderboard<std::shared_ptr<Viewer>>& lb);
    Leaderboard<std::shared_ptr<Viewer>> sortViewerBy(SortViewer sorter);
    Leaderboard<std::shared_ptr<User>> sortUsers();
    Leaderboard<std::shared_ptr<User>> sortUsers(const Leaderboard<std::shared_ptr<User>>& lb);
    Leaderboard<std::shared_ptr<User>> sortUserBy(SortUser sorter);
    Leaderboard<std::shared_ptr<Stream>> sortStreams();
    Leaderboard<std::shared_ptr<Stream>> sortStreams(const Leaderboard<std::shared_ptr<Stream>>& lb);
    Leaderboard<std::shared_ptr<Stream>> sortStreamsBy(SortStream sorter);

private:
    std::shared_ptr<ViewerManager> viewerManager;
    std::shared_ptr<StreamerManager> streamerManager;
    std::shared_ptr<StreamManager> streamManager;
    std::shared_ptr<UserManager> userManager;


};

#endif //PROJECT_LEADERBOARD_MANAGER_H
