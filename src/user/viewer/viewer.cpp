//
// Created by biromiro on 18/10/20.
//
#include "viewer.h"
#include "../../stream/stream.h"
#include "../../stream/privateStream/privateStream.h"


Viewer::Viewer(Date birthDate, std::string name, std::string nickname): User(birthDate,name,nickname, VIEWER){
    if(getAge() < 12){
        throw std::invalid_argument("Minimum Age Not Met");
    }
}

enum UserTypes Viewer::getUserType() const{
    return type;
}

bool Viewer::joinStream(Stream* stream){
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

bool Viewer::giveFeedbackToStream(std::string comment) {
    if(isWatchingStream() && currentStream->getStreamType() == PRIVATE ){
        PrivateStream* currentStreamPrivate = dynamic_cast<PrivateStream*>(currentStream);
        currentStreamPrivate->getComment(comment);
        return true;
    }else
        return false;
}

bool Viewer::followStreamer(Streamer *streamer) {
    if(followingStreamers.find(streamer) != followingStreamers.end())
        return false;
    else
        followingStreamers.insert(streamer);
    return true;
}

bool Viewer::unfollowStreamer(Streamer *streamer) {
    return followingStreamers.erase(streamer) != 0;
}

