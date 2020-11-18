//
// Created by biromiro on 28/10/20.
//

#include "leaderboard_manager.h"

#include <utility>


LeaderboardManager::LeaderboardManager(std::shared_ptr<ViewerManager> viewerManager, std::shared_ptr<StreamerManager> streamerManager,
                                       std::shared_ptr<StreamManager> streamManager, std::shared_ptr<UserManager> userManager):
                                       viewerManager(std::move(std::move(viewerManager))),
                                       streamManager(std::move(streamManager)),
                                       streamerManager(std::move(std::move(streamerManager))),
                                       userManager(std::move(userManager)){}

Leaderboard<std::shared_ptr<Stream>> LeaderboardManager::filterStreamByLanguage(enum StreamLanguage lang){
    std::vector<std::shared_ptr<Stream>> newLB = streamManager->getStreams();
    newLB.insert(newLB.begin(),streamManager->getCacheOfFinishedStreams().begin(),streamManager->getCacheOfFinishedStreams().end());
    newLB.erase(std::remove_if(newLB.begin(),newLB.end(),[&lang](const std::shared_ptr<Stream>& stream){return stream->getLanguage() != lang;}),newLB.end());
    return Leaderboard<std::shared_ptr<Stream>>(newLB);
}

Leaderboard<std::shared_ptr<Stream>> LeaderboardManager::filterStreamByGenre(StreamGenre genre){
    std::vector<std::shared_ptr<Stream>> newLB = streamManager->getStreams();
    newLB.insert(newLB.begin(),streamManager->getCacheOfFinishedStreams().begin(),streamManager->getCacheOfFinishedStreams().end());
    newLB.erase(std::remove_if(newLB.begin(),newLB.end(),[&genre](const std::shared_ptr<Stream>& stream){return stream->getGenre() != genre;}),newLB.end());
    return Leaderboard<std::shared_ptr<Stream>>(newLB);
}

Leaderboard<std::shared_ptr<Stream>> LeaderboardManager::filterStreamByAge(unsigned int minAge){
    std::vector<std::shared_ptr<Stream>> newLB = streamManager->getStreams();
    newLB.insert(newLB.begin(),streamManager->getCacheOfFinishedStreams().begin(),streamManager->getCacheOfFinishedStreams().end());
    newLB.erase(std::remove_if(newLB.begin(),newLB.end(),[&minAge](const std::shared_ptr<Stream>& stream){return stream->getMinAge() < minAge;}),newLB.end());
    return Leaderboard<std::shared_ptr<Stream>>(newLB);
}

Leaderboard<std::shared_ptr<Stream>> LeaderboardManager::filterStreamByStreamer(const std::string &nickname) {
    std::vector<std::shared_ptr<Stream>> newLB = streamManager->getStreams();
    newLB.insert(newLB.begin(),streamManager->getCacheOfFinishedStreams().begin(),streamManager->getCacheOfFinishedStreams().end());
    newLB.erase(std::remove_if(newLB.begin(),newLB.end(),[&nickname](const std::shared_ptr<Stream>& stream){return stream->getStreamer()->getNickname() != nickname;}),newLB.end());
    return Leaderboard<std::shared_ptr<Stream>>(newLB);
}


Leaderboard<std::shared_ptr<Stream>> LeaderboardManager::filterStreamByDate(const Date& date){
    std::vector<std::shared_ptr<Stream>> newLB = streamManager->getStreams();
    newLB.insert(newLB.begin(),streamManager->getCacheOfFinishedStreams().begin(),streamManager->getCacheOfFinishedStreams().end());
    newLB.erase(std::remove_if(newLB.begin(),newLB.end(),[&date](const std::shared_ptr<Stream>& stream){return stream->getStreamDate() != date;}),newLB.end());
    return Leaderboard<std::shared_ptr<Stream>>(newLB);
}

Leaderboard<std::shared_ptr<Stream>> LeaderboardManager::filterStreamByType(enum StreamType type){
    std::vector<std::shared_ptr<Stream>> newLB;
    if(type == StreamType::FINISHED) {
        newLB = streamManager->getCacheOfFinishedStreams();
        return Leaderboard<std::shared_ptr<Stream>>(newLB);
    }
    newLB = streamManager->getStreams();
    newLB.erase(std::remove_if(newLB.begin(),newLB.end(),[&type](const std::shared_ptr<Stream>& stream){return stream->getStreamType() != type;}),newLB.end());
    return Leaderboard<std::shared_ptr<Stream>>(newLB);
}

Leaderboard<std::shared_ptr<Streamer>> LeaderboardManager::sortStreamers() {
    std::vector<std::shared_ptr<Streamer>> newLB;
    newLB = streamerManager->getStreamers();
    std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Streamer>& s1, const std::shared_ptr<Streamer>& s2){return (*s1)>(*s2);});
    return Leaderboard<std::shared_ptr<Streamer>>(newLB);
}

Leaderboard<std::shared_ptr<Streamer>> LeaderboardManager::sortStreamers(const Leaderboard<std::shared_ptr<Streamer>>& lb) {
    std::vector<std::shared_ptr<Streamer>> newLB = lb.get();
    std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Streamer>& s1, const std::shared_ptr<Streamer>& s2){return (*s1)>(*s2);});
    return Leaderboard<std::shared_ptr<Streamer>>(newLB);
}

Leaderboard<std::shared_ptr<Viewer>> LeaderboardManager::sortViewers() {
    std::vector<std::shared_ptr<Viewer>> newLB;
    newLB = viewerManager->getViewers();
    std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Viewer>& s1, const std::shared_ptr<Viewer>& s2){return (*s1)>(*s2);});
    return Leaderboard<std::shared_ptr<Viewer>>(newLB);
}

Leaderboard<std::shared_ptr<Viewer>> LeaderboardManager::sortViewers(const Leaderboard<std::shared_ptr<Viewer>> &lb) {
    std::vector<std::shared_ptr<Viewer>> newLB = lb.get();
    std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Viewer>& s1, const std::shared_ptr<Viewer>& s2){return (*s1)>(*s2);});
    return Leaderboard<std::shared_ptr<Viewer>>(newLB);
}

Leaderboard<std::shared_ptr<User>> LeaderboardManager::sortUsers() {
    std::vector<std::shared_ptr<User>> newLB;
    newLB.reserve(userManager->getUsers().size());
    for (const auto& elem: userManager->getUsers()) {
        newLB.push_back(elem);
    }
    std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<User>& s1, const std::shared_ptr<User>& s2){return (*s1)>(*s2);});
    return Leaderboard<std::shared_ptr<User>>(newLB);
}

Leaderboard<std::shared_ptr<User>> LeaderboardManager::sortUsers(const Leaderboard<std::shared_ptr<User>> &lb) {
    std::vector<std::shared_ptr<User>> newLB = lb.get();
    std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<User>& s1, const std::shared_ptr<User>& s2){return (*s1)>(*s2);});
    return Leaderboard<std::shared_ptr<User>>(newLB);
}

Leaderboard<std::shared_ptr<Stream>> LeaderboardManager::sortStreams() {
    std::vector<std::shared_ptr<Stream>> newLB;
    newLB = streamManager->getStreams();
    std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Stream>& s1, const std::shared_ptr<Stream>& s2){return (*s1)>(*s2);});
    return Leaderboard<std::shared_ptr<Stream>>(newLB);
}

Leaderboard<std::shared_ptr<Stream>> LeaderboardManager::sortStreams(const Leaderboard<std::shared_ptr<Stream>> &lb) {
    std::vector<std::shared_ptr<Stream>> newLB = lb.get();
    std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Stream>& s1, const std::shared_ptr<Stream>& s2){return (*s1)>(*s2);});
    return Leaderboard<std::shared_ptr<Stream>>(newLB);
}

Leaderboard<std::shared_ptr<Stream>> LeaderboardManager::sortStreamsBy(SortStream sorter) {
    std::vector<std::shared_ptr<Stream>> newLB = sortStreams().get();
    switch (sorter) {
        case SortStream::MINIMUM_AGE:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Stream>& s1, const std::shared_ptr<Stream>& s2){return s1->getMinAge() < s2->getMinAge();});
            break;
        case SortStream::LANGUAGE:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Stream>& s1, const std::shared_ptr<Stream>& s2){return s1->getLanguage() < s2->getLanguage();});
            break;
        case SortStream::GENRE:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Stream>& s1, const std::shared_ptr<Stream>& s2){return s1->getGenre() < s2->getGenre();});
            break;
        case SortStream::VIEWS:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Stream>& s1, const std::shared_ptr<Stream>& s2){return s1->getNumOfViewers() < s2->getNumOfViewers();});
            break;
        case SortStream::LIKES:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Stream>& s1, const std::shared_ptr<Stream>& s2){return s1->getVotes().first < s2->getVotes().first;});
            break;
        case SortStream::DATE:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Stream>& s1, const std::shared_ptr<Stream>& s2){return s1->getStreamDate() < s2->getStreamDate();});
            break;
        case SortStream::TYPE:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Stream>& s1, const std::shared_ptr<Stream>& s2){return s1->getStreamType() < s2->getStreamType();});
            break;
        default:
            break;
    }
    return Leaderboard<std::shared_ptr<Stream>>(newLB);
}

Leaderboard<std::shared_ptr<Streamer>> LeaderboardManager::sortStreamerBy(SortStreamer sorter) {
    std::vector<std::shared_ptr<Streamer>> newLB = sortStreamers().get();
    switch (sorter) {
        case SortStreamer::NAME:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Streamer>& s1, const std::shared_ptr<Streamer>& s2){return s1->getName() < s2->getName();});
            break;
        case SortStreamer::NICKNAME:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Streamer>& s1, const std::shared_ptr<Streamer>& s2){return s1->getNickname() < s2->getNickname();});
            break;
        case SortStreamer::BIRTHDATE:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Streamer>& s1, const std::shared_ptr<Streamer>& s2){return s1->getBirthDate() < s2->getBirthDate();});
            break;
        case SortStreamer::JOINDATE:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Streamer>& s1, const std::shared_ptr<Streamer>& s2){return s1->getJoinDate() < s2->getJoinDate();});
            break;
        case SortStreamer::VIEWCOUNT:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Streamer>& s1, const std::shared_ptr<Streamer>& s2){return s1->getTotalViewCount() < s2->getTotalViewCount();});
            break;
        case SortStreamer::STREAMING:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Streamer>& s1, const std::shared_ptr<Streamer>& s2){return s1->isStreaming() < s2->isStreaming();});
            break;
        case SortStreamer::NUM_FOLLOWERS:
            auto streamerPtr = streamerManager;
            std::sort(newLB.begin(),newLB.end(),[&streamerPtr](const std::shared_ptr<Streamer>& s1, const std::shared_ptr<Streamer>& s2){return streamerPtr->getNumOfFollowers(s1) < streamerPtr->getNumOfFollowers(s2);});
            break;
    }
    return Leaderboard<std::shared_ptr<Streamer>>(newLB);
}

Leaderboard<std::shared_ptr<Viewer>> LeaderboardManager::sortViewerBy(SortViewer sorter) {
    std::vector<std::shared_ptr<Viewer>> newLB = sortViewers().get();
    switch (sorter) {
        case SortViewer::NAME:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Viewer>& s1, const std::shared_ptr<Viewer>& s2){return s1->getName() < s2->getName();});
            break;
        case SortViewer::NICKNAME:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Viewer>& s1, const std::shared_ptr<Viewer>& s2){return s1->getNickname() < s2->getNickname();});
            break;
        case SortViewer::BIRTHDATE:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Viewer>& s1, const std::shared_ptr<Viewer>& s2){return s1->getBirthDate() < s2->getBirthDate();});
            break;
        case SortViewer::JOINDATE:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Viewer>& s1, const std::shared_ptr<Viewer>& s2){return s1->getJoinDate() < s2->getJoinDate();});
            break;
        case SortViewer::WATCHING_STREAM:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Viewer>& s1, const std::shared_ptr<Viewer>& s2){return s1->isWatchingStream() < s2->isWatchingStream();});
            break;
        case SortViewer::NUM_OF_WATCHED_STREAMS:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Viewer>& s1, const std::shared_ptr<Viewer>& s2){return s1->getStreamHistory().size() < s2->getStreamHistory().size();});
            break;
    }
    return Leaderboard<std::shared_ptr<Viewer>>(newLB);
}

Leaderboard<std::shared_ptr<User>> LeaderboardManager::sortUserBy(SortUser sorter) {
    std::vector<std::shared_ptr<User>> newLB = sortUsers().get();
    switch (sorter) {
        case SortUser::NAME:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<User>& s1, const std::shared_ptr<User>& s2){return s1->getName() < s2->getName();});
            break;
        case SortUser::NICKNAME:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<User>& s1, const std::shared_ptr<User>& s2){return s1->getNickname() < s2->getNickname();});
            break;
        case SortUser::BIRTHDATE:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<User>& s1, const std::shared_ptr<User>& s2){return s1->getBirthDate() < s2->getBirthDate();});
            break;
        case SortUser::JOINDATE:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<User>& s1, const std::shared_ptr<User>& s2){return s1->getJoinDate() < s2->getJoinDate();});
            break;
        case SortUser::USERTYPE:
            std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<User>& s1, const std::shared_ptr<User>& s2){return s1->getUserType() < s2->getUserType();});
            break;
    }
    return Leaderboard<std::shared_ptr<User>>(newLB);
}

Leaderboard<std::shared_ptr<Streamer>> LeaderboardManager::getFollowingStreamersLeaderboard(std::shared_ptr<Viewer> viewer) {
    auto followingStreamers = viewer->getFollowingStreamers();
    std::vector<std::shared_ptr<Streamer>> streamers;
    streamers.reserve(followingStreamers.size());
    for(const auto& elem: followingStreamers){
        streamers.push_back(streamerManager->get(elem));
    }
    return Leaderboard<std::shared_ptr<Streamer>>(streamers);
}

Leaderboard<std::shared_ptr<Streamer>>
LeaderboardManager::getNotFollowingStreamersLeaderboard(std::shared_ptr<Viewer> viewer) {
    auto followingStreamersNicknames = viewer->getFollowingStreamers();
    auto allFollowingStreamers = streamerManager->getStreamers();
    std::vector<std::shared_ptr<Streamer>> followingStreamers;
    followingStreamers.reserve(followingStreamers.size());
    for(const auto& elem: followingStreamersNicknames){
        followingStreamers.push_back(streamerManager->get(elem));
    }
    std::vector<std::shared_ptr<Streamer>> notFollowingStreamers;
    notFollowingStreamers.reserve(allFollowingStreamers.size()-followingStreamers.size());
    for(const auto& elem: allFollowingStreamers){
        if(find(followingStreamers.begin(),followingStreamers.end(),elem) == followingStreamers.end())
            notFollowingStreamers.push_back(elem);
    }
    return Leaderboard<std::shared_ptr<Streamer>>(notFollowingStreamers);
}

