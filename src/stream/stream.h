//
// Created by biromiro on 13/10/20.
//

#ifndef PROJECT_STREAM_H
#define PROJECT_STREAM_H


#include "../user/user.h"
#include <iostream>

class Stream {
private:
    unsigned minAge;
    std::string title;
    std::string lang;
public:
    Stream(std::string title, std::string lang, unsigned int minAge);
    unsigned getMinAge() const;
    std::string getTitle() const;
    std::string getLanguage() const;
    bool canJoin(Viewer newViewer) const;
};

class PrivateStream: public Stream {
public:
    PrivateStream(std::string title, std::string lang, unsigned minAge);
};

class PublicStream: public Stream {
public:
    PublicStream(std::string title, std::string lang, unsigned minAge);
};

#endif //PROJECT_STREAM_H