//
// Created by emanu on 21-Oct-20.
//


#include <vector>

#ifndef SRC_LEADERBOARD_H
#define SRC_LEADERBOARD_H

template<class N>
class LeaderBoard{
private:
    std::vector<N> topTen;
public:
    LeaderBoard(){}
    void setTopTen(std::vector<N> vec){}
    void getTopTen(){}
};

#endif //SRC_LEADERBOARD_H
