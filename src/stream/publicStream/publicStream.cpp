//
// Created by biromiro on 18/10/20.
//

#include "publicStream.h"

PublicStream::PublicStream(std::string title, enum StreamLanguage lang, unsigned int minAge, std::shared_ptr<Streamer> streamer): Stream(std::move(title), lang, minAge, PUBLIC, streamer){}

enum StreamType PublicStream::getStreamType() const {
    return type;
}