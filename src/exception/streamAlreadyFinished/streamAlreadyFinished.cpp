//
// Created by Danny on 18/11/2020.
//

#include "streamAlreadyFinished.h"

StreamAlreadyFinished::StreamAlreadyFinished(std::shared_ptr<Stream> stream, const std::string &message) : stream(stream), message(message), std::invalid_argument(message) {}

const std::string & StreamAlreadyFinished::getMessage() { return message; }