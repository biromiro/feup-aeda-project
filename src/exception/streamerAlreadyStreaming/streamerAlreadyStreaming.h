//
// Created by Danny on 18/11/2020.
//

#ifndef PROJECT_STREAMERALREADYSTREAMING_H
#define PROJECT_STREAMERALREADYSTREAMING_H

#include <iostream>
#include <exception>
#include "../../model/user/streamer/streamer.h"

class StreamerAlreadyStreaming : std::invalid_argument {
public:
    StreamerAlreadyStreaming(std::shared_ptr<Streamer> streamer, const std::string & message);
    const std::string & getMessage();
private:
    std::shared_ptr<Streamer> streamer;
    std::string message;
};

#endif //PROJECT_STREAMERALREADYSTREAMING_H
