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
    return currentStream != NULL;
}

bool Viewer::leaveCurrentStream() {
    if(isWatchingStream()){
        currentStream = NULL;
        return true;
    }
    return false;
}

bool Viewer::giveFeedbackToStream(enum FeedbackLikeSystem feedback) {
    return isWatchingStream() && currentStream->addFeedback(feedback);
}

bool Viewer::giveFeedbackToStream(std::string comment) {
    if(currentStream->getStreamType() == PRIVATE ){
        PrivateStream* currentStreamPrivate = dynamic_cast<PrivateStream*>(currentStream);
        currentStreamPrivate->addComment(comment);
        return true;
    }else
        return false;
}

bool Viewer::giveFeedbackToStream(enum FeedbackLikeSystem feedback, std::string comment) {
    if(!isWatchingStream()){
        return false;
    }
    if(!(currentStream->addFeedback(feedback)))
        return false;

    return giveFeedbackToStream(comment);
}

bool Viewer::followStreamer(Streamer *streamer) {
    unsigned int initSize = followingStreamers.size();
    auto it = std::find_if(followingStreamers.begin(),followingStreamers.end(),[streamer](Streamer* streamer1){return streamer==streamer1;});
    if(it != followingStreamers.end())
        return false;
    else
        followingStreamers.push_back(streamer);
    return true;
}

bool Viewer::unfollowStreamer(Streamer *streamer) {
    unsigned int initSize = followingStreamers.size();
    followingStreamers.erase(std::remove_if(followingStreamers.begin(),followingStreamers.end(),
                                            [streamer](Streamer* streamer1){return streamer==streamer1;})
                             ,followingStreamers.end());
    return initSize == followingStreamers.size();
}

