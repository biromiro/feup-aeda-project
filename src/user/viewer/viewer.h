//
// Created by biromiro on 18/10/20.
//

#include "../user.h"
#include <vector>

#ifndef PROJECT_VIEWER_H
#define PROJECT_VIEWER_H

enum FeedbackLikeSystem{
    LIKE,
    DISLIKE
};

class Stream;

class Viewer: public User{
public:
    Viewer(unsigned int age, std::string name, std::string nickname);
    enum UserTypes getUserType() const override;
    bool joinStream(Stream* stream);
    bool isWatchingStream() const;
    bool leaveCurrentStream();
    bool giveFeedbackToStream(enum FeedbackLikeSystem);
    bool giveFeedbackToStream(enum FeedbackLikeSystem, std::string comment);

private:
    Stream* currentStream;
    std::vector<Stream*> streamHistory;
};

#endif //PROJECT_VIEWER_H
