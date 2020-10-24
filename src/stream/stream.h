//
// Created by biromiro on 13/10/20.
//

#ifndef PROJECT_STREAM_H
#define PROJECT_STREAM_H


#include "../user/user.h"
#include <iostream>

enum FeedbackLikeSystem{
    LIKE,
    DISLIKE,
    INVALID_VOTE
};

enum StreamType{
    PRIVATE,
    PUBLIC
};

class Viewer;

class Stream {
public:
    Stream(std::string title, std::string lang, unsigned int minAge, enum StreamType type);
    unsigned getMinAge() const;
    std::string getTitle() const;
    std::string getLanguage() const;
    bool canJoin(Viewer* newViewer) const;
    bool getFeedback(enum FeedbackLikeSystem feedback);
    virtual enum StreamType getStreamType() const = 0;
protected:
    unsigned int minAge;
    std::string title;
    std::string lang;
    enum StreamType type;
    std::pair<unsigned int,unsigned int> votingSystem;
};

#endif //PROJECT_STREAM_H