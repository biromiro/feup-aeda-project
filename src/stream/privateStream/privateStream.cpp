//
// Created by biromiro on 18/10/20.
//

#include "privateStream.h"
#include "../../user/viewer/viewer.h"

PrivateStream::PrivateStream(std::string title, enum StreamLanguage lang, unsigned int minAge): Stream(std::move(title), lang, minAge, PRIVATE){};

enum StreamType PrivateStream::getStreamType() const { return type; }

std::vector<std::string> PrivateStream::getWhitelist() const { return whitelist; }

unsigned int PrivateStream::getMaxNumViewers() const { return maxNumViewers; }

std::vector<std::string> PrivateStream::getComments() const { return comments; }

bool PrivateStream::addToWhitelist(Viewer* v){
    whitelist.push_back(v->getNickname());
    return true;
}

bool PrivateStream::setMaxNumViewers(unsigned int maxNumViewers) {
    this->maxNumViewers = maxNumViewers;
    if(this->maxNumViewers == maxNumViewers) { return true; }
    else { return false; }
}

void PrivateStream::addComment(const std::string& comment) {
    comments.push_back(comment);
}