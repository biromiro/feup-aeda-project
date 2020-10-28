//
// Created by biromiro on 18/10/20.
//

#include "streamer.h"

#include <utility>

Streamer::Streamer(Date birthDate, std::string name, std::string nickname): User(birthDate,std::move(name),std::move(nickname), STREAMER) {
    if(getAge() < 15){
        throw std::invalid_argument("Minimum Age Not Met");
    }
    currentStream = nullptr;
    previousStreams = std::vector<Stream*>();
    totalViewCount = 0;
}

enum UserTypes Streamer::getUserType() const{
    return type;
}

bool Streamer::isStreaming(){
    return currentStream != nullptr;
}

void Streamer::setStream(Stream *stream) {
    currentStream = stream;
}


void Streamer::removeStream() {
    previousStreams.push_back(currentStream);
    currentStream = nullptr;
}

