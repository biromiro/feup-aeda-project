//
// Created by biromiro on 18/10/20.
//
#include "viewer.h"

#include <utility>
#include <fstream>
#include "../../stream/privateStream/privateStream.h"
#include "../../stream/streamManager.h"


Viewer::Viewer() : User(VIEWER) {}

Viewer::Viewer(Date birthDate, std::string name, std::string nickname, std::string password): User(birthDate,std::move(name),std::move(nickname), VIEWER, password){
    if(getAge() < 12){
        throw InvalidAge(getAge(), "You have to be at least 12 years old!");
    }
    currentStream = nullptr;
}

bool Viewer::joinStream(const std::shared_ptr<Stream>& stream){
    std::shared_ptr<Viewer> thisViewer = shared_from_this();
    if(stream->canJoin(thisViewer) && currentStream == nullptr){
        stream->newViewerJoin();
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
        currentStream->viewerLeft();
        currentStream = nullptr;
        return true;
    }
    return false;
}

bool Viewer::giveFeedbackToStream(enum FeedbackLikeSystem feedback) {
    return isWatchingStream() && currentStream->addFeedback(feedback);
}

bool Viewer::giveFeedbackToStream(const std::string& comment) {
    if(isWatchingStream() && currentStream->getStreamType() == PRIVATE ){
        auto currentStreamPrivate = std::dynamic_pointer_cast<PrivateStream>(currentStream);
        currentStreamPrivate->addComment(comment);
        return true;
    }else
        return false;
}

bool Viewer::followStreamer(const std::shared_ptr<Streamer>& streamer) {
    std::string nickname = streamer->getNickname();
    if(followingStreamers.find(nickname) != followingStreamers.end())
        return false;
    else
        followingStreamers.insert(nickname);
    return true;
}

bool Viewer::unfollowStreamer(const std::shared_ptr<Streamer>& streamer) {
    std::string nickname = streamer->getNickname();
    return followingStreamers.erase(nickname) != 0;
}

const std::shared_ptr<Stream> &Viewer::getCurrentStream() const {
    return currentStream;
}

const std::vector<std::shared_ptr<Stream>> &Viewer::getStreamHistory() const {
    return streamHistory;
}

const std::unordered_set<std::string> &Viewer::getFollowingStreamers() const {
    return followingStreamers;
}

bool Viewer::operator<(const Viewer &rhs) const {
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

bool Viewer::operator>(const Viewer &rhs) const {
    return rhs < *this;
}

bool Viewer::operator<=(const Viewer &rhs) const {
    return !(rhs < *this);
}

bool Viewer::operator>=(const Viewer &rhs) const {
    return !(*this < rhs);
}

bool Viewer::operator==(const Viewer &rhs) const {
    return nickname == rhs.nickname;
}

bool Viewer::operator!=(const Viewer &rhs) const {
    return !(rhs == *this);
}

void Viewer::readData(std::ifstream &ifs, const std::shared_ptr<StreamManager>& streamManager) {
    unsigned int streamHistorySize, currentStreamID, streamIDFromHistory, followingStreamersSize;
    std::string newStreamerID;
    std::shared_ptr<Stream> streamInHistory;
    ifs >> currentStreamID;
    if(currentStreamID != 0)
        currentStream = streamManager->get(currentStreamID);
    ifs >> streamHistorySize;
    while (streamHistorySize--){
        ifs >> streamIDFromHistory;
        streamInHistory = streamManager->get(streamIDFromHistory);
        if(streamInHistory != nullptr)
            streamHistory.push_back(streamInHistory);
    }
    ifs >> followingStreamersSize;
    ifs.ignore();
    while(followingStreamersSize--){
        getline(ifs,newStreamerID);
        followingStreamers.insert(newStreamerID);
    }
    User::readData(ifs);
}

void Viewer::writeData(std::ofstream &ofs) {
    ofs << ((currentStream != nullptr) ? currentStream->getUniqueId() : 0) << "\n";
    ofs << streamHistory.size() << "\n";
    for(const auto& elem: streamHistory){
        ofs << elem->getUniqueId() << "\n";
    }
    ofs << followingStreamers.size() << "\n";
    for(const auto& elem: followingStreamers){
        ofs << elem << "\n";
    }
    User::writeData(ofs);
}