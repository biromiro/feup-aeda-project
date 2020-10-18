//
// Created by biromiro on 18/10/20.
//

#include <vector>
#include "../user.h"
#include "../../stream/stream.h"


#ifndef PROJECT_STREAMER_H

class Streamer: public User{
public:
    Streamer(unsigned int age, std::string name, std::string nickname);
    enum UserTypes getUserType() const;

private:
    std::vector<Stream*> previousStreams;
};

#define PROJECT_STREAMER_H

#endif //PROJECT_STREAMER_H
