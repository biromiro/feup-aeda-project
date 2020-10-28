//
// Created by biromiro on 18/10/20.
//

#include <vector>
#include "../user.h"
#include "../../stream/stream.h"


#ifndef PROJECT_STREAMER_H

class Stream;

class Streamer: public User{
public:
    Streamer(Date birthDate, std::string name, std::string nickname);
    enum UserTypes getUserType() const override;
    bool isStreaming();
    void setStream(Stream* stream);
    void removeStream();

private:
    std::vector<Stream*> previousStreams;
    Stream* currentStream;
    unsigned int totalViewCount;
};

#define PROJECT_STREAMER_H

#endif //PROJECT_STREAMER_H
