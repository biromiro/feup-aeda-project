//
// Created by biromiro on 18/10/20.
//

#include "../user.h"
#include "../../stream/stream.h"
#include <algorithm>

#ifndef PROJECT_VIEWER_H
#define PROJECT_VIEWER_H

class Stream;

class Viewer: public User{
public:
    Viewer(Date birthDate, std::string name, std::string nickname);
    enum UserTypes getUserType() const override;
    bool joinStream(Stream* stream);
    bool isWatchingStream() const;
    bool leaveCurrentStream();
    bool giveFeedbackToStream(enum FeedbackLikeSystem feedback);
    bool giveFeedbackToStream(std::string comment);
    bool giveFeedbackToStream(enum FeedbackLikeSystem feedback, std::string comment);
    bool followStreamer(Streamer* streamer);
    bool unfollowStreamer(Streamer* streamer);

private:
    Stream* currentStream;
    std::vector<Stream*> streamHistory;
    std::vector<Streamer*> followingStreamers;
};

#endif //PROJECT_VIEWER_H
