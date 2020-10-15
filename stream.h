//
// Created by biromiro on 13/10/20.
//
#include "viewer.h"

#ifndef PROJECT_STREAM_H
#define PROJECT_STREAM_H

class Stream {
private:
    unsigned minAge;
    string title;
    string lang;
public:
    Stream(string title, string lang, unsigned minAge);
    unsigned getMinAge() const;
    string getTitle() const;
    string getLanguage() const;
    bool canJoin(Viewer newViewer) const;

};

class PrivateStream: public Stream {
public:
    PrivateStream(string title, string lang, unsigned minAge)
};

class PublicStream: public Stream {
public:
    PublicStream(string title, string lang, unsigned minAge)
};

#endif //PROJECT_STREAM_H