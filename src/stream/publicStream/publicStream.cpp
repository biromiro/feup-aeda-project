//
// Created by biromiro on 18/10/20.
//

#include "publicStream.h"

PublicStream::PublicStream(std::string title, enum StreamLanguage lang, unsigned int minAge): Stream(std::move(title), lang, minAge, PUBLIC){}

enum StreamType PublicStream::getStreamType() const {
    return type;
}