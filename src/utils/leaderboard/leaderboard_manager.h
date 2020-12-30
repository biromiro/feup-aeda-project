//
// Created by biromiro on 28/10/20.
//

#ifndef PROJECT_LEADERBOARD_MANAGER_H
#define PROJECT_LEADERBOARD_MANAGER_H

#include "../../model/user/viewer/viewer_manager.h"
#include "../../model/user/streamer/streamer_manager.h"
#include "leaderboard.h"


/**
 * Defines the ways a stream can be sorted
 */
enum class SortStream{
    MINIMUM_AGE,
    LANGUAGE,
    GENRE,
    VIEWS,
    LIKES,
    DATE,
    TYPE
};

/*
 * Defines the ways a user can be sorted
 */
enum class SortUser{
    NAME,
    NICKNAME,
    BIRTHDATE,
    JOINDATE,
    USERTYPE
};

/*
 * Defines the ways a viewe can be sorted
 */
enum class SortViewer{
    NAME,
    NICKNAME,
    BIRTHDATE,
    JOINDATE,
    WATCHING_STREAM,
    NUM_OF_WATCHED_STREAMS
};

/*
 * Defines the ways a streamer can be sorted
 */
enum class SortStreamer{
    NAME,
    NICKNAME,
    BIRTHDATE,
    JOINDATE,
    VIEWCOUNT,
    STREAMING,
    NUM_FOLLOWERS
};


/**
 * @file leaderboard_manager.cpp
 *
 * @brief Manages the leaderboards of the platform
 *
 * @ingroup utils
 */

/**
 * Implementation of a Leaderboard Manager Class
 *
 * Wraps information of a vector and overloads the output operator for a better and clearer print
 */
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

    /**
     * Gets the leaderboard showing the streamer a given viewer follows
     *
     * @param viewer the viewer
     * @return a leaderboard with the following streamers
     */
    Leaderboard<std::shared_ptr<Streamer>> getFollowingStreamersLeaderboard(const std::shared_ptr<Viewer>& viewer);

    /**
     * Gets the leaderboard showing the streamer a given viewer does not follow
     *
     * @param viewer the viewer
     * @return a leaderboard with the not following streamers
     */
    Leaderboard<std::shared_ptr<Streamer>> getNotFollowingStreamersLeaderboard(const std::shared_ptr<Viewer>& viewer);

    /**
     * Sorts all streamers with a given sorter
     *
     * @param sorter the sorter
     * @return the sorted streamer leaderboard
     */
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
    static Leaderboard<std::shared_ptr<Viewer>> sortViewers(const Leaderboard<std::shared_ptr<Viewer>>& lb);

    /**
     * Sorts all viewers with a given sorter
     *
     * @param sorter the sorter
     * @return the sorted viewer leaderboard
     */
    Leaderboard<std::shared_ptr<Viewer>> sortViewerBy(SortViewer sorter);

    /**
     * Filters all viewers by a given minimum age
     *
     * @param age the age to filter
     * @return the leaderboard of the viewers older than age
     */
    Leaderboard<std::shared_ptr<Viewer>> filterViewerByAge(unsigned int age);

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
    static Leaderboard<std::shared_ptr<User>> sortUsers(const Leaderboard<std::shared_ptr<User>>& lb);

    /**
     * Sorts all users with a given sorter
     *
     * @param sorter the sorter
     * @return the sorted user leaderboard
     */
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
    static Leaderboard<std::shared_ptr<Stream>> sortStreams(const Leaderboard<std::shared_ptr<Stream>>& lb);

    /**
    * Sorts all streams with a given sorter
    *
    * @param sorter the sorter
    * @return the sorted stream leaderboard
    */
    Leaderboard<std::shared_ptr<Stream>> sortStreamsBy(SortStream sorter);

    /**
     * Sorts a given stream vector with a given sorter
     *
     * @param sorter the sorter
     * @param newLB the vector to sort
     * @return the sorted stream leaderboard
     */
    static Leaderboard<std::shared_ptr<Stream>> sortStreamsBy(SortStream sorter, std::vector<std::shared_ptr<Stream>> newLB);

    /**
     * Gets the top10 streams given a sorter
     *
     * @param sorter the sorter
     * @return the top10 stream leaderboard
     */
    Leaderboard<std::shared_ptr<Stream>> top10StreamsBy(SortStream sorter);

    /**
     * Gets the total number of active streams
     *
     * @return the total number of active streams
     */
    unsigned int totalNumberOfStreams();

    /**
     * Gets the total number of active private streams
     *
     * @return the total number of active private streams
     */
    unsigned int totalNumberOfPrivateStreams();

    /**
     * Gets the total number of active public streams
     *
     * @return the total number of active public streams
     */
    unsigned int totalNumberOfPublicStreams();

    /**
     * Gets the mean of views per active stream
     *
     * @return the mean of views per active stream
     */
    unsigned int meanViewsPerStreamActive();

    /**
     * Gets the mean of views per finished stream
     *
     * @return the mean of views per finished stream
     */
    unsigned int meanViewsPerStreamFinished();

    /**
     * Gets the most common language
     *
     * @return the most common language
     */
    StreamLanguage mostCommonLanguage();

    /**
     * Gets the most common type
     *
     * @return the most common type
     */
    StreamType mostCommonType();

    /**
     * Gets the nickname of the streamer with the most views
     *
     * @return the nickname of the streamer with the most views
     */
    std::string mostViewsStreamer();

    /**
     * Filters the streamers which have a deactivated account
     *
     * @return returns the streamers with a deactivated account*/
    Leaderboard<std::shared_ptr<Streamer>> filterDeactivatedStreamers();

    /**
     * Filters the viewers which have a deactivated account
     *
     * @return returns the viewers with a deactivated account
     */
    Leaderboard<std::shared_ptr<Viewer>> filterDeactivatedViewers();

    /**
     * Filters the users which have a deactivated account
     *
     * @return returns the users with a deactivated account
     */
    Leaderboard<std::shared_ptr<User>> filterDeactivatedUsers();

    /**
     * Shows the donations in an ordered fashion
     *
     * @param ammount the minimum ammount of a donation
     * @return the ordered leaderboard of donations
     */
    Leaderboard<Donation> getOrderedDonations(float ammount = 0);

    /**
     * Shows the donations that are within an interval of streamerWorkRating values
     *
     * @param lowerBound the lowest value
     * @param upperBound the highest value
     * @param ammount the minimum ammount of a donation
     * @return the ordered leaderboard of donations with the given filter
     */
    Leaderboard<Donation> getDonationsByAvalInterval(streamerWorkRating lowerBound, streamerWorkRating upperBound, float ammount = 0);

private:
    std::shared_ptr<ViewerManager> viewerManager;
    std::shared_ptr<StreamerManager> streamerManager;
    std::shared_ptr<StreamManager> streamManager;
    std::shared_ptr<UserManager> userManager;
};

#endif //PROJECT_LEADERBOARD_MANAGER_H
