//
// Created by biromiro on 18/10/20.
//

#include "privateStream.h"
#include "../../user/viewer/viewer.h"

PrivateStream::PrivateStream() : Stream(StreamType::PRIVATE){}

PrivateStream::PrivateStream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamGenre genre, std::shared_ptr<Streamer> streamer): Stream(std::move(title), lang, minAge, StreamType::PRIVATE, genre, streamer){};

enum StreamType PrivateStream::getStreamType() const { return type; }

std::vector<std::string> PrivateStream::getWhitelist() const { return whitelist; }

unsigned int PrivateStream::getMaxNumViewers() const { return maxNumViewers; }

std::vector<std::string> PrivateStream::getComments() const { return comments; }

bool PrivateStream::addToWhitelist(std::shared_ptr<Viewer> v){
    std::string v_nick = v->getNickname();
    if (std::find(whitelist.begin(), whitelist.end(), v_nick) == whitelist.end()){
        whitelist.push_back(v_nick);
        return true;
    }
    return false;
}

bool PrivateStream::removeFromWhitelist(std::shared_ptr<Viewer> v){
    std::string v_nick = v->getNickname();
    auto itr = std::find(whitelist.begin(), whitelist.end(), v_nick);
    if (itr != whitelist.end()){
        whitelist.erase(itr);
        return true;
    }
    return false;
}

bool PrivateStream::setMaxNumViewers(unsigned int maxNumViewers) {
    this->maxNumViewers = maxNumViewers;
    if(this->maxNumViewers == maxNumViewers) { return true; }
    else { return false; }
}

void PrivateStream::addComment(const std::string& comment) {
    comments.push_back(comment);
}

bool PrivateStream::canJoin(const std::shared_ptr<Viewer>& newViewer) const {
    if (newViewer->getAge() < minAge || maxNumViewers < (numOfViewers + 1)) { return false; }
    for (auto nickname: whitelist) {
        if (newViewer->getNickname() == nickname) { return true; }
    }
    return false;
}

void PrivateStream::readData(std::ifstream &ifs, std::shared_ptr<StreamerManager> streamerManager) {
    unsigned int whitelistSize, commentsSize;
    std::string temp;

    ifs >> whitelistSize;
    ifs.ignore();
    while(whitelistSize--) {
        getline(ifs, temp);
        whitelist.push_back(temp);
    }

    ifs >> commentsSize;
    ifs.ignore();
    while (commentsSize--){
        getline(ifs,temp);
        comments.push_back(temp);
    }

    ifs >> maxNumViewers;

    Stream::readData(ifs, streamerManager);
}

void PrivateStream::writeData(std::ofstream &ofs) {
    ofs << whitelist.size() << "\n";
    for(const auto& elem: whitelist)
        ofs << elem << "\n";


    ofs << comments.size() << "\n";

    for(const auto& elem: comments)
        ofs << elem << "\n";

    ofs << maxNumViewers;
    Stream::writeData(ofs);
}


