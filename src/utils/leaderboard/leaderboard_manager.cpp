//
// Created by biromiro on 28/10/20.
//

#include "leaderboard_manager.h"

LeaderboardManager::LeaderboardManager(ViewerManager *viewerManager, StreamerManager *streamerManager,
                                       StreamManager *streamManager, UserManager* userManager):
                                       viewerManager(viewerManager),
                                       streamManager(streamManager),
                                       streamerManager(streamerManager),
                                       userManager(userManager){}

Leaderboard<std::shared_ptr<Stream>> LeaderboardManager::filterStreamByLanguage(enum StreamLanguage lang){
    std::vector<std::shared_ptr<Stream>> newLB = streamManager->getStreams();
    newLB.insert(newLB.begin(),streamManager->getCacheOfFinishedStreams().begin(),streamManager->getCacheOfFinishedStreams().end());
    newLB.erase(std::remove_if(newLB.begin(),newLB.end(),[&lang](const std::shared_ptr<Stream>& stream){return stream->getLanguage() != lang;}),newLB.end());
    return Leaderboard<std::shared_ptr<Stream>>(newLB);
}

Leaderboard<std::shared_ptr<Stream>> LeaderboardManager::filterStreamByGenre(enum StreamGenre genre){
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
    if(type == FINISHED) {
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
    for (auto it = userManager->getUsers().begin(); it != userManager->getUsers().end(); ) {
        newLB.push_back(std::move(userManager->getUsers().extract(it++).value()));
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

/*
std::vector<N> sortByViews(){
    std::vector<N> newLB = this->leaderBoard;
    std::sort(newLB.begin(),newLB.end(),[](std::shared_ptr<Stream> streamA,std::shared_ptr<Stream> streamB){return streamA->getViewerCount > streamB.getViewerCount();});
    return newLB;
}*/
/*std::vector<N> sortByLikes(){
    std::vector<N> newLB = this->leaderBoard;
    std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Stream>& streamA,const std::shared_ptr<Stream>& streamB){return streamA->addFeedback(LIKE) > streamB->addFeedback(LIKE);});
    return newLB;
}
//std::vector<N> getLeaderBoard(){return this->leaderBoard;}
std::vector<N> getTopN(unsigned int n){
    unsigned int i = 0;
    std::vector<N> newLB;
    while(n && i <this->leaderBoard.size()){
        newLB.push_back(this->leaderBoard[i]);
        i++;
        n--;
    }
    return newLB;
}
*/