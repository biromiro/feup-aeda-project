//
// Created by Danny on 15/10/2020.
//
#include "stream.h"
#include "../user/viewer/viewer.h"
#include <iostream>
#include <utility>

unsigned int Stream::nextID = 0;

Stream::Stream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamType type, std::shared_ptr<Streamer> streamer): title(std::move(title)), language(lang), minAge(minAge), type(type), streamer(streamer) {
    uniqueID = ++nextID;
}

unsigned int Stream::getNumOfViewers() const { return numOfViewers; }

unsigned Stream::getMinAge() const { return minAge; }

std::string Stream::getTitle() const { return title; }

enum StreamLanguage Stream::getLanguage() const { return language; }

bool Stream::canJoin(std::shared_ptr<Viewer> newViewer) const {
    return newViewer->getAge() >= minAge;
}

Date Stream::getStreamDate() const { return streamDate; }

std::shared_ptr<Streamer> Stream::getStreamer() const { return streamer; }

std::pair<unsigned int, unsigned int> Stream::getVotes() const { return votingSystem; }

unsigned int Stream::getViewerCount() const { return uniqueViewerCount; }

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
