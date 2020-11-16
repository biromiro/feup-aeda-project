//
// Created by biromiro on 18/10/20.
//

#include "publicStream.h"

PublicStream::PublicStream() : Stream(StreamType::PUBLIC){}

PublicStream::PublicStream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamGenre genre, std::shared_ptr<Streamer> streamer): Stream(std::move(title), lang, minAge, StreamType::PUBLIC, genre, streamer){}

enum StreamType PublicStream::getStreamType() const {
    return type;
}

void PublicStream::readData(std::ifstream &ifs, std::shared_ptr<StreamerManager> streamerManager) {
    Stream::readData(ifs,streamerManager);
}

void PublicStream::writeData(std::ofstream &ofs) {
    Stream::writeData(ofs);
}


