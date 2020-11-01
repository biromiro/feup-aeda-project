//
// Created by emanu on 21-Oct-20.
//


#include <vector>
#include <memory>
#include <algorithm>
#include "../../stream/stream.h"
#include "../date/date.h"

#ifndef SRC_LEADERBOARD_H
#define SRC_LEADERBOARD_H

/*enum SortOrFilterType{
    AGE,
    LANGUAGE,
    GENRE,
    VIEWS,
    LIKES,
    DATE,
    PRIVATE,
    PUBLIC
};*/

enum Language{
    AF, AR, AZ,  BE, BG, CA, CZ, CY, DA, DE, EL, EN, EO, ES, ET, EU,
    FA ,FI, FO, FR, GL, GU, HE, HI, HR, HU, HY, ID, IS, IT, JA, KA,
    KK, KN, KO, KOK, KY, LT, LV, MI ,MK, MN, MR, MS, MT, NB, NL, NN,
    NS, PA, PL, PS, PT_BR, PT_PT, QU, RO, RU, SA ,SE, SK, SL, SQ, SR,
    SV, SW, SYR, TA, TE, TH, TL, TN, TR, TT, TS, UK, UR, UZ, YI, XH, ZH
};


template<class N>
class LeaderBoard{
private:
    std::vector<N> leaderBoard;
public:
    LeaderBoard(){}
    LeaderBoard(std::vector<N> leaderBoard){
        this->leaderBoard = leaderBoard;
    }
    std::vector<N> filterStreamByLanguage(enum Language lang){
        std::vector<N> newLB = this->leaderBoard;
        std::remove_if(newLB.begin(),newLB.end(),[&lang](std::shared_ptr<Stream> stream){return stream->getLanguage() != lang;});
        return newLB;
    }
    std::vector<N> filterStreamByAge(unsigned int minAge){
        std::vector<N> newLB = this->leaderBoard;
        std::remove_if(newLB.begin(),newLB.end(),[&minAge](std::shared_ptr<Stream> stream){return stream->getMinAge() < minAge;});
        return newLB;
    }
    /*
    std::vector<N> filterStreamByDate(Date date){
        std::vector<N> newLB = this->leaderBoard;
        std::remove_if(newLB.begin(),newLB.end(),[&date](std::shared_ptr<Stream> stream){return stream.getDate() != date;});
        return newLB;
    }*/
    std::vector<N> filterStreamByType(enum StreamType type){
        std::vector<N> newLB = this->leaderBoard;
        std::remove_if(newLB.begin(),newLB.end(),[&type](std::shared_ptr<Stream> stream){return stream->getStreamType() != type;});
        return newLB;
    }
    /*
    std::vector<N> sortByViews(){
        std::vector<N> newLB = this->leaderBoard;
        std::sort(newLB.begin(),newLB.end(),[](std::shared_ptr<Stream> streamA,std::shared_ptr<Stream> streamB){return streamA->getViewerCount > streamB.getViewerCount();});
        return newLB;
    }*/
    std::vector<N> sortByLikes(){
        std::vector<N> newLB = this->leaderBoard;
        std::sort(newLB.begin(),newLB.end(),[](std::shared_ptr<Stream> streamA,std::shared_ptr<Stream> streamB){return streamA->getFeedback(LIKE) > streamB->getFeedback(LIKE);});
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
};

#endif //SRC_LEADERBOARD_H
