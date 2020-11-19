//
// Created by Danny on 18/11/2020.
//

#ifndef PROJECT_STREAMERALREADYSTREAMING_H
#define PROJECT_STREAMERALREADYSTREAMING_H

#include <iostream>
#include <exception>
#include "../../model/user/streamer/streamer.h"

class StreamerAlreadyStreaming : public std::logic_error {
public:
    StreamerAlreadyStreaming(std::shared_ptr<Streamer> streamer, const std::string & message);

    [[nodiscard]] const std::shared_ptr<Streamer> &getStreamer() const;

private:
    std::shared_ptr<Streamer> streamer;
};

#endif //PROJECT_STREAMERALREADYSTREAMING_H
