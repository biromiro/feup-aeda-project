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
    previousStreams = std::vector<std::shared_ptr<Stream>>();
    totalViewCount = 0;
}

bool Streamer::isStreaming(){
    return currentStream != nullptr;
}

void Streamer::setStream(const std::shared_ptr<Stream>& stream) {
    currentStream = stream;
}


void Streamer::removeStream() {
    previousStreams.push_back(currentStream);
    currentStream = nullptr;
}

unsigned int Streamer::getTotalViewCount() const {
    return totalViewCount;
}

const std::shared_ptr<Stream> &Streamer::getCurrentStream() const {
    return currentStream;
}

