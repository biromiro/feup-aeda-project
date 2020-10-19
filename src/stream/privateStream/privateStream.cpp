//
// Created by biromiro on 18/10/20.
//

#include "privateStream.h"

PrivateStream::PrivateStream(std::string title, std::string lang, size_t minAge): Stream(title, lang, minAge, PRIVATE){};

enum StreamType PrivateStream::getStreamType() const {
    return type;
}

void PrivateStream::getComment(std::string comment) {
    comments.push_back(comment);
}