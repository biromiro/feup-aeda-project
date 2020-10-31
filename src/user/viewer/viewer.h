//
// Created by biromiro on 18/10/20.
//

#include "../user.h"
#include "../../stream/stream.h"
#include <algorithm>
#include <unordered_set>

#ifndef PROJECT_VIEWER_H
#define PROJECT_VIEWER_H

class Stream;

class Viewer: public User{
public:
    /**
     * Constructor of the Viewer Class
     *
     * @param birthDate the birth date of the viewer
     * @param name the name of the viewer
     * @param nickname the nickname of the viewer
     */
    Viewer(Date birthDate, std::string name, std::string nickname);

    /**
     * Getter of the type of User
     *
     * @return the user's type (in this case, VIEWER)
     */
    enum UserTypes getUserType() const override;

    /**
     * Joins/Sets the current stream
     *
     * @param stream the stream to join
     * @return True if the action was successful, false otherwise
     */
    bool joinStream(Stream* stream);

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
    bool followStreamer(Streamer* streamer);

    /**
     * Unfollows a new streamer
     *
     * @param streamer the streamer to unfollow
     * @return True if the viewer can unfollow the given streamer, false otherwise
     */
    bool unfollowStreamer(Streamer* streamer);

private:
    Stream* currentStream;
    std::vector<Stream*> streamHistory;
    std::unordered_set<Streamer*> followingStreamers;
};

#endif //PROJECT_VIEWER_H
