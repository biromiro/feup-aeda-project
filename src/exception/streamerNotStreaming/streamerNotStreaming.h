//
// Created by biromiro on 19/11/20.
//

#ifndef PROJECT_STREAMERNOTSTREAMING_H
#define PROJECT_STREAMERNOTSTREAMING_H

#include <iostream>

class StreamerNotStreaming : public std::logic_error {
public:
    explicit StreamerNotStreaming(const std::string & message);
};


#endif //PROJECT_STREAMERNOTSTREAMING_H
