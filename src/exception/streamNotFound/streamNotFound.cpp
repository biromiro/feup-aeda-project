//
// Created by Danny on 18/11/2020.
//

#include "streamNotFound.h"

StreamNotFound::StreamNotFound(std::shared_ptr<Stream> stream, const std::string &message) : stream(std::move(std::move(stream))), message(message), std::invalid_argument(message) {}

const std::string & StreamNotFound::getMessage() { return message; }