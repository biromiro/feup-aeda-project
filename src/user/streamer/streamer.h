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
    bool startPublicStream(std::string title, enum StreamLanguage lang, unsigned int minAge);
    bool startPrivateStream(std::string title, enum StreamLanguage lang, unsigned int minAge);
    bool endStream();

private:
    std::vector<Stream*> previousStreams;
    Stream* currentStream;
    unsigned int totalViewCount;
};

#define PROJECT_STREAMER_H

#endif //PROJECT_STREAMER_H
