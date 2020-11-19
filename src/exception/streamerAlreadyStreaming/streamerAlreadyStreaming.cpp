//
// Created by Danny on 18/11/2020.
//

#include "streamerAlreadyStreaming.h"

StreamerAlreadyStreaming::StreamerAlreadyStreaming(std::shared_ptr<Streamer> streamer, const std::string &message) : streamer(std::move(std::move(streamer))), message(message), std::invalid_argument(message) {}

const std::string & StreamerAlreadyStreaming::getMessage() { return message; }
