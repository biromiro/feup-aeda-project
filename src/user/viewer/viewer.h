//
// Created by biromiro on 18/10/20.
//

#include "../user.h"
#include <vector>

#ifndef PROJECT_VIEWER_H
#define PROJECT_VIEWER_H

enum feedbackLikeSystem{
    like,
    dislike
};

class Stream;

class Viewer: public User{
public:
    Viewer(unsigned int age, std::string name, std::string nickname);
    virtual enum UserTypes getUserType() const;
    bool joinStream(Stream* stream);
    bool isWatchingStream();
    bool leaveCurrentStream();
    bool giveFeedbackToStream(enum feedbackLikeSystem);
    bool giveFeedbackToStream(enum feedbackLikeSystem, std::string comment);

private:
    Stream* currentStream;
    std::vector<Stream*> streamHistory;
};

#endif //PROJECT_VIEWER_H
