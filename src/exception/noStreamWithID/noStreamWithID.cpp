//
// Created by Danny on 18/11/2020.
//

#include "noStreamWithID.h"

NoStreamWithID::NoStreamWithID(unsigned int streamID, const std::string &message) : streamID(streamID), message(message), std::invalid_argument(message) {}

const std::string & NoStreamWithID::getMessage() { return message; }

unsigned int NoStreamWithID::getStreamId() const {
    return streamID;
}
