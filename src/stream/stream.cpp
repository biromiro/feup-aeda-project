//
// Created by Danny on 15/10/2020.
//
#include "stream.h"
#include "../user/viewer/viewer.h"
#include <iostream>
#include <utility>

unsigned int Stream::nextID = 0;

Stream::Stream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamType type, enum StreamGenre genre, std::shared_ptr<Streamer> streamer): title(std::move(title)), language(lang), minAge(minAge), type(type), genre(genre), streamer(std::move(streamer)) {
    uniqueID = ++nextID;
    votingSystem = std::pair<unsigned int,unsigned int>();
    numOfViewers = 0;
}

unsigned int Stream::getNumOfViewers() const { return numOfViewers; }

unsigned Stream::getMinAge() const { return minAge; }

std::string Stream::getTitle() const { return title; }

enum StreamLanguage Stream::getLanguage() const { return language; }

bool Stream::canJoin(const  std::shared_ptr<Viewer>& newViewer) const {
    return newViewer->getAge() >= minAge;
}

Date Stream::getStreamDate() const { return streamDate; }

std::shared_ptr<Streamer> Stream::getStreamer() const { return streamer; }

std::pair<unsigned int, unsigned int> Stream::getVotes() const { return votingSystem; }

bool Stream::addFeedback(enum FeedbackLikeSystem feedback) {
    if(feedback == LIKE)
        votingSystem.first++;
    else if(feedback == DISLIKE)
        votingSystem.second++;
    else
        return false;
    return true;
}

void Stream::setNumOfViewers(unsigned int numOfViewers) { this->numOfViewers = numOfViewers; }

bool Stream::operator==(std::shared_ptr<Stream> stream) const { return uniqueID == stream->getUniqueId(); }

unsigned int Stream::getUniqueId() const { return uniqueID; }

StreamGenre Stream::getGenre() const {
    return genre;
}

StreamType Stream::getType() const {
    return type;
}

bool Stream::operator<(const Stream &rhs) const {
    if (type < rhs.type)
        return true;
    if (rhs.type < type)
        return false;
    if (streamDate < rhs.streamDate)
        return true;
    if (rhs.streamDate < streamDate)
        return false;
    if (votingSystem.first < rhs.votingSystem.first)
        return true;
    if (rhs.votingSystem.first < votingSystem.first)
        return false;
    if (votingSystem.second < rhs.votingSystem.second)
        return true;
    if (rhs.votingSystem.second < votingSystem.second)
        return false;
    if (numOfViewers < rhs.numOfViewers)
        return true;
    if (rhs.numOfViewers < numOfViewers)
        return false;
    if (uniqueID < rhs.uniqueID)
        return true;
    if (rhs.uniqueID < uniqueID)
        return false;
    if (minAge < rhs.minAge)
        return true;
    if (rhs.minAge < minAge)
        return false;
    if (title < rhs.title)
        return true;
    if (rhs.title < title)
        return false;
    if (language < rhs.language)
        return true;
    if (rhs.language < language)
        return false;
    if (genre < rhs.genre)
        return true;
    if (rhs.genre < genre)
        return false;
    return genre < rhs.genre;
}

bool Stream::operator>(const Stream &rhs) const {
    return rhs < *this;
}

bool Stream::operator<=(const Stream &rhs) const {
    return !(rhs < *this);
}

bool Stream::operator>=(const Stream &rhs) const {
    return !(*this < rhs);
}

bool Stream::operator==(const Stream &rhs) const {
    return uniqueID == rhs.uniqueID;
}

bool Stream::operator!=(const Stream &rhs) const {
    return !(rhs == *this);
}

std::ostream& operator<<(std::ostream& out, StreamLanguage f) {
    std::array<std::string,80> e{{"AF","AR","AZ","BE","BG","CA","CZ","CY","DA","DE","EL","EN",
                                    "EO","ES","ET","EU","FA","FI","FO","FR","GL","GU","HE","HI",
                                    "HR","HU","HY","ID","IS","IT","JA","KA","KK","KN","KO","KOK",
                                    "KY","LT","LV","MI ","MK","MN","MR", "MS","MT","NB","NL","NN",
                                    "NS","PA","PL","PS","PT_BR","PT_PT","QU","RO","RU","SA ","SE",
                                    "SK","SL","SQ","SR","SV","SW","SYR"," TA","TE","TH","TL"," TN",
                                    "TR","TT","TS","UK","UR","UZ","YI","XH","ZH"}};
    out << e.at(f);
    return out;
}

std::ostream& operator<<(std::ostream& out, StreamType f) {
    switch (f) {
        case PUBLIC: out << "Public"; break;
        case PRIVATE: out << "Private"; break;
        case FINISHED: out << "Finished"; break;
        default: out << int(f); break;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, StreamGenre f) {
    switch (f) {
        case MUSIC: out << "Music"; break;
        case GAMING: out << "Gaming"; break;
        case COOKING: out << "Cooking"; break;
        case TALKSHOW: out << "Talkshow"; break;
        default: out << int(f); break;
    }
    return out;
}
