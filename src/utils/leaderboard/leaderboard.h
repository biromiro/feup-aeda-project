//
// Created by biromiro on 01/11/20.
//

#ifndef PROJECT_LEADERBOARD_H
#define PROJECT_LEADERBOARD_H

#include <iostream>
#include <vector>
#include <memory>
#include "../../stream/stream.h"
#include "../date/date.h"
#include <ostream>

template <class N>
class Leaderboard{
public:
    Leaderboard(std::vector<N> vec): leaderboard(vec){};

    friend std::ostream& operator<<(std::ostream& os, const Leaderboard<N>& dt){
        if constexpr(std::is_same_v<N, std::shared_ptr<Streamer>>) {
            os << "Streamer Leaderboard\n\n";
            os << std::left << std::setfill(' ') << std::setw(20) <<  "Nickname" << std::setw(20) <<  "Name"
                    << std::setw(20) <<  "View Count" << std::setw(20) <<  "Streaming?" <<  std::setw(20) <<  "Stream ID"
                    << "Join Date";
            os << "\n\n" << std::left;
            for(const auto& elem: dt.leaderboard){
                os << std::left << std::setw(20) << elem->getNickname() << std::setw(20) <<
                elem->getName() << std::setw(20) << 
                elem->getTotalViewCount() << std::setw(20) <<  (elem->isStreaming() ? "Yes" : "No") << std::setw(20)
                << (elem->isStreaming() ? std::to_string((elem->getCurrentStream())->getUniqueId()) : "-") << elem->getJoinDate() << "\n";
            }
        }else if constexpr (std::is_same_v<N, std::shared_ptr<Viewer>>){
            return os;
        }else if constexpr (std::is_same_v<N, std::shared_ptr<User>>){
            return os;
        }else if constexpr (std::is_same_v<N, std::shared_ptr<Stream>>){
            return os;
        }else
            return os;
    }

private:
    std::vector<N> leaderboard;
};

#endif //PROJECT_LEADERBOARD_H
