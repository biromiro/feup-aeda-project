//
// Created by biromiro on 18/10/20.
//

#include "privateStream.h"
#include "../../../exception/userNotFound/userNotFound.h"

PrivateStream::PrivateStream() : Stream(StreamType::PRIVATE){}

PrivateStream::PrivateStream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamGenre genre, std::shared_ptr<Streamer> streamer):
        Stream(std::move(title), lang, minAge, StreamType::PRIVATE, genre, std::move(streamer)){}

enum StreamType PrivateStream::getStreamType() const {
    return type;
}

std::vector<std::string> PrivateStream::getWhitelist() const {
    return whitelist;
}

unsigned int PrivateStream::getMaxNumViewers() const {
    return maxNumViewers;
}

std::map<std::string,std::string> PrivateStream::getComments() const {
    return comments;
}

bool PrivateStream::addToWhitelist(const std::shared_ptr<Viewer>& v){

    if(v == nullptr) throw UserNotFound(std::dynamic_pointer_cast<User>(v), "That user is invalid!");

    std::string v_nick = v->getNickname();

    //sees if a given user is already in the whitelist
    if (std::find(whitelist.begin(), whitelist.end(), v_nick) == whitelist.end()){
        whitelist.push_back(v_nick);
        return true;
    }

    throw NicknameAlreadyAdded(v_nick, "Viewer you're trying to add is already on the whitelist!");
}

bool PrivateStream::removeFromWhitelist(const std::shared_ptr<Viewer>& v){

    std::string v_nick = v->getNickname();

    auto itr = std::find(whitelist.begin(), whitelist.end(), v_nick);

    //checks if the user is, in fact, in the whitelist
    if (itr != whitelist.end()){
        whitelist.erase(itr);
        return true;
    }
    throw NicknameNotFound(v_nick, "Viewer is not on the whitelist!");
}

void PrivateStream::setMaxNumViewers(unsigned int newMaxNumViewers) {
    maxNumViewers = newMaxNumViewers;
}

void PrivateStream::addComment(const std::string& nickname, const std::string& comment) {
    //adds a new comment to the comment map, associating the user to its comment
    comments.insert(std::pair<std::string,std::string>(nickname,comment));
}

bool PrivateStream::canJoin(const std::shared_ptr<Viewer>& newViewer) const {

    if (newViewer->getAge() < minAge || maxNumViewers <= (numOfViewers + 1)) {
        return false;
    }

    return std::any_of(whitelist.begin(),whitelist.end(),[&newViewer](const auto& nickname){
        return newViewer->getNickname() == nickname;
    });
}

void PrivateStream::readData(std::ifstream &ifs, const std::shared_ptr<StreamerManager>& streamerManager) {

    unsigned int whitelistSize = 0, commentsSize = 0;
    std::string temp1,temp2;

    ifs >> whitelistSize;
    ifs.ignore();

    while(whitelistSize--) {
        getline(ifs, temp1);
        whitelist.push_back(temp1);
    }

    ifs >> commentsSize;
    ifs.ignore();

    while (commentsSize--){
        getline(ifs,temp1);
        getline(ifs, temp2);
        comments.insert(std::pair<std::string,std::string>(temp1,temp2));
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
        ofs << elem.first << "\n" << elem.second << "\n";

    ofs << maxNumViewers << "\n";

    Stream::writeData(ofs);
}


