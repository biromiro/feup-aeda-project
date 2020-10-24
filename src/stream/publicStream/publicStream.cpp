//
// Created by biromiro on 18/10/20.
//

#include "publicStream.h"

PublicStream::PublicStream(std::string title, std::string lang, unsigned int minAge): Stream(title, lang, minAge, PUBLIC){};

enum StreamType PublicStream::getStreamType() const {
    return type;
}