//
// Created by biromiro on 28/10/20.
//

#include "leaderboard_manager.h"

LeaderboardManager::LeaderboardManager(ViewerManager *viewerManager, StreamerManager *streamerManager,
                                       StreamManager *streamManager): viewerManager(viewerManager), streamManager(streamManager), streamerManager(streamerManager){}

Leaderboard<std::shared_ptr<Stream>> LeaderboardManager::filterStreamByLanguage(enum StreamLanguage lang){
    std::vector<std::shared_ptr<Stream>> newLB = streamManager->getStreams();
    newLB.erase(std::remove_if(newLB.begin(),newLB.end(),[&lang](const std::shared_ptr<Stream>& stream){return stream->getLanguage() != lang;}),newLB.end());
    return Leaderboard<std::shared_ptr<Stream>>(newLB);
}
Leaderboard<std::shared_ptr<Stream>> LeaderboardManager::filterStreamByAge(unsigned int minAge){
    std::vector<std::shared_ptr<Stream>> newLB = streamManager->getStreams();
    newLB.erase(std::remove_if(newLB.begin(),newLB.end(),[&minAge](const std::shared_ptr<Stream>& stream){return stream->getMinAge() < minAge;}),newLB.end());
    return Leaderboard<std::shared_ptr<Stream>>(newLB);
}

Leaderboard<std::shared_ptr<Stream>> LeaderboardManager::filterStreamByDate(const Date& date){
    std::vector<std::shared_ptr<Stream>> newLB = streamManager->getStreams();
    newLB.erase(std::remove_if(newLB.begin(),newLB.end(),[&date](const std::shared_ptr<Stream>& stream){return stream->getStreamDate() != date;}),newLB.end());
    return Leaderboard<std::shared_ptr<Stream>>(newLB);
}

Leaderboard<std::shared_ptr<Stream>> LeaderboardManager::filterStreamByType(enum StreamType type){
    std::vector<std::shared_ptr<Stream>> newLB;
    if(type == FINISHED)
        newLB = streamManager->getCacheOfFinishedStreams();
    else
        newLB = streamManager->getStreams();
    newLB.erase(std::remove_if(newLB.begin(),newLB.end(),[&type](const std::shared_ptr<Stream>& stream){return stream->getStreamType() != type;}),newLB.end());
    return Leaderboard<std::shared_ptr<Stream>>(newLB);
}

Leaderboard<std::shared_ptr<Streamer>> LeaderboardManager::sortStreamersByNickname() {
    std::vector<std::shared_ptr<Streamer>> newLB;
    newLB = streamerManager->getStreamers();
    std::sort(newLB.begin(),newLB.end(),[](const std::shared_ptr<Streamer>& s1, const std::shared_ptr<Streamer>& s2)
                {return s1->getNickname() < s2->getNickname();});
    return Leaderboard<std::shared_ptr<Streamer>>(newLB);
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