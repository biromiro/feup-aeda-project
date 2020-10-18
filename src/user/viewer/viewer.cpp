//
// Created by biromiro on 18/10/20.
//

#include "viewer.h"
#include "../../stream/stream.h"


Viewer::Viewer(unsigned int age, std::string name, std::string nickname): User(age,name,nickname){
    if(age < 12){
        throw std::invalid_argument("Minimum Age Not Met");
    }
}

enum UserTypes Viewer::getUserType() const{
    return VIEWER;
}

bool Viewer::joinStream(Stream* stream){
    if(stream->canJoin(this)){
        currentStream = stream;
        //need to add viewer to stream viewers
    }
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

bool Viewer::giveFeedbackToStream(enum FeedbackLikeSystem) {

}

bool Viewer::giveFeedbackToStream(enum FeedbackLikeSystem, std::string comment) {

}