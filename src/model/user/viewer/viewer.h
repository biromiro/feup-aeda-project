//
// Created by biromiro on 18/10/20.
//


#ifndef PROJECT_VIEWER_H
#define PROJECT_VIEWER_H

#include "../user.h"
#include "../../stream/stream.h"
#include "../streamer/streamer.h"
#include "../../../exception/invalidAge/invalidAge.h"
#include <algorithm>
#include <memory>
#include <unordered_set>

class StreamManager;

class Stream;

class Viewer: public User,  public std::enable_shared_from_this<Viewer>{
public:

    Viewer();

    /**
     * Constructor of the Viewer Class
     *
     * @param birthDate the birth date of the viewer
     * @param name the name of the viewer
     * @param nickname the nickname of the viewer
     */
    Viewer(Date birthDate, std::string name, std::string nickname, std::string password);

    /**
     * Joins/Sets the current stream
     *
     * @param stream the stream to join
     * @return True if the action was successful, false otherwise
     */
    bool joinStream(const std::shared_ptr<Stream>& stream);

    /**
     * Checks if the viewer is watching a stream
     *
     * @return True if the viewer is watching a stream, false otherwise
     */
    bool isWatchingStream() const;

    /**
     * Leaves the current stream
     *
     * @return True if the viewer was watching a stream (and leaves successfully), false otherwise
     */
    bool leaveCurrentStream();

    /**
     * Gives feedback to a given stream
     *
     * @param feedback the feedback to be given to a stream
     * @return True if the feedback was given successfully, false otherwise
     */
    bool giveFeedbackToStream(enum FeedbackLikeSystem feedback);

    /**
     * Gives a comment to a given stream
     *
     * @param comment the comment to be given to a stream
     * @return True if the comment was given successfully, false otherwise
     */
    bool giveFeedbackToStream(const std::string& comment);

    /**
     * Follows a new streamer
     *
     * @param streamer the streamer to follow
     * @return True if the viewer can follow the given streamer, false otherwise
     */
    bool followStreamer(const std::shared_ptr<Streamer>& streamer);

    /**
     * Unfollows a new streamer
     *
     * @param streamer the streamer to unfollow
     * @return True if the viewer can unfollow the given streamer, false otherwise
     */
    bool unfollowStreamer(const std::shared_ptr<Streamer>& streamer);

    /**
     * Getter of current stream
     *
     * @return the current stream
     */
    const std::shared_ptr<Stream> &getCurrentStream() const;

    /**
     * Getter of the stream history
     *
     * @return the stream history
     */
    std::map<std::shared_ptr<Stream>,FeedbackLikeSystem> &getStreamHistory();

    /**
     * Getter of the following streamers unordered set
     *
     * @return the unordered set of the following streamers
     */
    const std::unordered_set<std::string> &getFollowingStreamers() const;

    void readData(std::ifstream &ist, const std::shared_ptr<StreamManager>& streamManager);

    void writeData(std::ofstream &ost) override;

    bool operator<(const Viewer &rhs) const;
    bool operator>(const Viewer &rhs) const;
    bool operator<=(const Viewer &rhs) const;
    bool operator==(const Viewer &rhs) const;
    bool operator!=(const Viewer &rhs) const;
    bool operator>=(const Viewer &rhs) const;

private:
    std::shared_ptr<Stream> currentStream;
    std::map<std::shared_ptr<Stream>, FeedbackLikeSystem> streamHistory;
    std::unordered_set<std::string> followingStreamers;
    FeedbackLikeSystem votedInStream;
};

#endif //PROJECT_VIEWER_H
