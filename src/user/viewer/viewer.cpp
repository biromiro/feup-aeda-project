//
// Created by biromiro on 18/10/20.
//
#include "viewer.h"

#include <utility>

#include "../../stream/privateStream/privateStream.h"


Viewer::Viewer(Date birthDate, std::string name, std::string nickname): User(birthDate,std::move(name),std::move(nickname), VIEWER){
    if(getAge() < 12){
        throw std::invalid_argument("Minimum Age Not Met");
    }
    currentStream = nullptr;
}

bool Viewer::joinStream(const std::shared_ptr<Stream>& stream){
    if(stream->canJoin(this)){
        currentStream = stream;
        return true;
    }
    return false;
}

bool Viewer::isWatchingStream() const{
    return currentStream != nullptr;
}

bool Viewer::leaveCurrentStream() {
    if(isWatchingStream()){
        streamHistory.push_back(currentStream);
        currentStream = nullptr;
        return true;
    }
    return false;
}

bool Viewer::giveFeedbackToStream(enum FeedbackLikeSystem feedback) {
    return isWatchingStream() && currentStream->getFeedback(feedback);
}

bool Viewer::giveFeedbackToStream(const std::string& comment) {
    if(isWatchingStream() && currentStream->getStreamType() == PRIVATE ){
        auto currentStreamPrivate = std::dynamic_pointer_cast<PrivateStream>(currentStream);
        currentStreamPrivate->getComment(comment);
        return true;
    }else
        return false;
}

bool Viewer::followStreamer(const std::shared_ptr<Streamer>& streamer) {
    if(followingStreamers.find(streamer) != followingStreamers.end())
        return false;
    else
        followingStreamers.insert(streamer);
    return true;
}

bool Viewer::unfollowStreamer(const std::shared_ptr<Streamer>& streamer) {
    return followingStreamers.erase(streamer) != 0;
}

const std::shared_ptr<Stream> &Viewer::getCurrentStream() const {
    return currentStream;
}

const std::vector<std::shared_ptr<Stream>> &Viewer::getStreamHistory() const {
    return streamHistory;
}

const std::unordered_set<std::shared_ptr<Streamer>> &Viewer::getFollowingStreamers() const {
    return followingStreamers;
}

