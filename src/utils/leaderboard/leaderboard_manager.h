//
// Created by biromiro on 28/10/20.
//

#ifndef PROJECT_LEADERBOARD_MANAGER_H
#define PROJECT_LEADERBOARD_MANAGER_H

#include "../../model/user/viewer/viewer_manager.h"
#include "../../model/user/streamer/streamer_manager.h"
#include "leaderboard.h"


enum class SortStream{
    MINIMUM_AGE,
    LANGUAGE,
    GENRE,
    VIEWS,
    LIKES,
    DATE,
    TYPE
};

enum class SortUser{
    NAME,
    NICKNAME,
    BIRTHDATE,
    JOINDATE,
    USERTYPE
};

enum class SortViewer{
    NAME,
    NICKNAME,
    BIRTHDATE,
    JOINDATE,
    WATCHING_STREAM,
    NUM_OF_WATCHED_STREAMS
};

enum class SortStreamer{
    NAME,
    NICKNAME,
    BIRTHDATE,
    JOINDATE,
    VIEWCOUNT,
    STREAMING,
    NUM_FOLLOWERS
};

class LeaderboardManager{
public:
    /**
     * LeaderboardManager Constructor
     *
     * @param streamerManager sets the streamerManager
     * @param streamManager sets the streamManager
     * @param userManager sets the userManager
     * @param viewerManager sets the viewerManager
     */
     LeaderboardManager(std::shared_ptr<ViewerManager> viewerManager,std::shared_ptr<StreamerManager> streamerManager,std::shared_ptr<StreamManager> streamManager, std::shared_ptr<UserManager> userManager);
    
    /**
     * Creates Leaderboard of streams of the selected language
     *
     * @param lang selected language
     * @return Leaderboard of streams of the selected language
     */
    Leaderboard<std::shared_ptr<Stream>> filterStreamByLanguage(StreamLanguage lang);
  
    /**
     * Creates Leaderboard of streams of the selected Genre
     *
     * @param genre selected genre
     * @return Leaderboard of streams of the selected genre
     */
    Leaderboard<std::shared_ptr<Stream>> filterStreamByGenre(StreamGenre genre);
    /**
     * Creates Leaderboard of streams with age above selected age
     *
     * @param minAge the minimum stream age
     * @return Leaderboard of streams with age > minAge
     */
    Leaderboard<std::shared_ptr<Stream>> filterStreamByAge(unsigned int minAge);
    /**
     * Creates Leaderboard of streams of the selected streamer
     *
     * @param nickname the streamer's name
     * @return Leaderboard of streams produced by the selected streamer
     */
    Leaderboard<std::shared_ptr<Stream>> filterStreamByStreamer(const std::string& nickname);
    /**
     * Creates Leaderboard of streams in the selected date
     *
     * @param date selected date
     * @return Leaderboard of streams aired in the selected date
     */
    Leaderboard<std::shared_ptr<Stream>> filterStreamByDate(const Date &date);
    /**
     * Creates Leaderboard of streams of the selected type
     *
     * @param type selected type
     * @return Leaderboard of streams of the selected type
     */
    Leaderboard<std::shared_ptr<Stream>> filterStreamByType(StreamType type);
    /**
     * Sorts Leaderboard by streamer's joindate > age > nickname > name
     *
     * @return sorted Leaderboard of streamers
     */
    Leaderboard<std::shared_ptr<Streamer>> sortStreamers();

    Leaderboard<std::shared_ptr<Streamer>> getFollowingStreamersLeaderboard(std::shared_ptr<Viewer> viewer);

    Leaderboard<std::shared_ptr<Streamer>> getNotFollowingStreamersLeaderboard(std::shared_ptr<Viewer> viewer);

    /**
     * Sorts the given Streamer Leaderboard by streamer's joindate > age > nickname > name
     *
     * @param lb Leaderboard of Streamers to sort
     * @return sorted Leaderboard of streamers
     */
    Leaderboard<std::shared_ptr<Streamer>> sortStreamers(const Leaderboard<std::shared_ptr<Streamer>>& lb);

    Leaderboard<std::shared_ptr<Streamer>> sortStreamerBy(SortStreamer sorter);
  
    /**
     * Sorts the Leaderboard by viewer's joindate > age > nickname > name
     *
     * @return sorted Leaderboard of viewers
     */
    Leaderboard<std::shared_ptr<Viewer>> sortViewers();
  
    /**
     * Sorts the given Viewer Leaderboard by viewer's joindate > age > nickname > name
     *
     * @param lb Leaderboard of viewers to sort
     * @return sorted Leaderboard of viewers
     */
    Leaderboard<std::shared_ptr<Viewer>> sortViewers(const Leaderboard<std::shared_ptr<Viewer>>& lb);

    Leaderboard<std::shared_ptr<Viewer>> sortViewerBy(SortViewer sorter);

    /**
     * Sorts the Leaderboard by user's joindate > age > nickname > name
     *
     * @return sorted Leaderboard of users
     */
    Leaderboard<std::shared_ptr<User>> sortUsers();
  
    /**
     * Sorts the given User Leaderboard by user's joindate > age > nickname > name
     *
     * @param lb Leaderboard of viewers to sort
     * @return sorted Leaderboard of viewers
     */
    Leaderboard<std::shared_ptr<User>> sortUsers(const Leaderboard<std::shared_ptr<User>>& lb);

    Leaderboard<std::shared_ptr<User>> sortUserBy(SortUser sorter);
  
    /**
     * Sorts the Leaderboard by Stream's type > date > likes > dislikes > views > ID > minAge > utils > lang > genre
     *
     * @return sorted Leaderboard of streams
     */
    Leaderboard<std::shared_ptr<Stream>> sortStreams();
  
    /**
     * Sorts the given Stream Leaderboard by Stream's type > date > likes > dislikes > views > ID > minAge > utils > lang > genre
     *
     * @param lb Leaderboard of streams to sort
     * @return sorted Leaderboard of streams
     */
  
    Leaderboard<std::shared_ptr<Stream>> sortStreams(const Leaderboard<std::shared_ptr<Stream>>& lb);
    Leaderboard<std::shared_ptr<Stream>> sortStreamsBy(SortStream sorter);

private:
    std::shared_ptr<ViewerManager> viewerManager;
    std::shared_ptr<StreamerManager> streamerManager;
    std::shared_ptr<StreamManager> streamManager;
    std::shared_ptr<UserManager> userManager;


};

#endif //PROJECT_LEADERBOARD_MANAGER_H
