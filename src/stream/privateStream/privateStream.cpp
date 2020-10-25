//
// Created by biromiro on 18/10/20.
//

#include "privateStream.h"

PrivateStream::PrivateStream(std::string title, enum StreamLanguage lang, unsigned int minAge): Stream(std::move(title), lang, minAge, PRIVATE){};

enum StreamType PrivateStream::getStreamType() const {
    return type;
}

void PrivateStream::getComment(const std::string& comment) {
    comments.push_back(comment);
}