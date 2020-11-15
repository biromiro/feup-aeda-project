//
// Created by biromiro on 18/10/20.
//

#include "streamer.h"

#include <utility>
#include <fstream>

Streamer::Streamer() : User(STREAMER) {}

Streamer::Streamer(Date birthDate, std::string name, std::string nickname, std::string password): User(birthDate,std::move(name),std::move(nickname), STREAMER, password) {
    if(getAge() < 15){
        throw InvalidAge(getAge(), "You have to be at least 15 years old!");
    }
    currentStreamID = 0;
    previousStreamsIDs = std::vector<unsigned int>();
    totalViewCount = 0;
}

bool Streamer::isStreaming(){
    return currentStreamID != 0;
}

void Streamer::setStream(const std::shared_ptr<Stream>& stream) {
    currentStreamID = stream->getUniqueId();
}


void Streamer::removeStream() {
    previousStreamsIDs.push_back(currentStreamID);
    currentStreamID = 0;
}

unsigned int Streamer::getTotalViewCount() const {
    return totalViewCount;
}

unsigned int Streamer::getCurrentStreamID() const {
    return currentStreamID;
}


bool Streamer::operator<(const Streamer &rhs) const {
    if (joinDate < rhs.joinDate)
        return true;
    if (rhs.joinDate < joinDate)
        return false;
    if (birthDate < rhs.birthDate)
        return true;
    if (rhs.birthDate < birthDate)
        return false;
    if (nickname < rhs.nickname)
        return true;
    if (rhs.nickname < nickname)
        return false;
    if (name < rhs.name)
        return true;
    if (rhs.name < name)
        return false;
    return type < rhs.type;
}

bool Streamer::operator>(const Streamer &rhs) const {
    return rhs < *this;
}

bool Streamer::operator<=(const Streamer &rhs) const {
    return !(rhs < *this);
}

bool Streamer::operator>=(const Streamer &rhs) const {
    return !(*this < rhs);
}

bool Streamer::operator==(const Streamer &rhs) const {
    return nickname == rhs.nickname;
}

bool Streamer::operator!=(const Streamer &rhs) const {
    return !(rhs == *this);
}

void Streamer::readData(std::ifstream& ifs) {
    unsigned int previousStreamSize, streamID;
    ifs >> previousStreamSize;

    while (previousStreamSize--){
        ifs >> streamID;
        previousStreamsIDs.push_back(streamID);
    }

    ifs >> currentStreamID;
    ifs >> totalViewCount;
    User::readData(ifs);
}

void Streamer::writeData(std::ofstream& ofs) {
    ofs << previousStreamsIDs.size() << "\n";
    for(const auto& elem: previousStreamsIDs){
        ofs << elem << "\n";
    }
    ofs << currentStreamID << "\n";
    ofs << totalViewCount << "\n";
    User::writeData(ofs);
}