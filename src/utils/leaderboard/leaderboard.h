//
// Created by biromiro on 01/11/20.
//

#ifndef PROJECT_LEADERBOARD_H
#define PROJECT_LEADERBOARD_H

#include <iostream>
#include <vector>
#include <memory>
#include<type_traits>
#include "../../model/stream/stream.h"
#include "../date/date.h"
#include <ostream>

template <class N>
class Leaderboard{
public:
    /**
     * Leaderboard constructor
     *
     * @param vec the vector representing the leaderboard
     */
    Leaderboard(const std::vector<N>& vec): leaderboard(vec){};

    /**
     * Output Stream operator overload
     *
     * @param os the output stream to print to
     * @param dt the leaderboard to print
     * @return the output stream given as input (allows chain input)
     */
    friend std::ostream& operator<<(std::ostream& os, const Leaderboard<N>& dt) {
        if constexpr (std::is_same_v<N, std::shared_ptr<Streamer>>) {
            os << "Streamer Leaderboard\n\n";
            os << std::left << std::setfill(' ') << std::setw(20) << "Nickname" << std::setw(20) << "Name"
               << std::setw(20) << "View Count" << std::setw(20) << "Streaming?" << std::setw(20) << "Stream ID"
               << std::setw(20) << "Birth Date" << std::setw(20) << "Join Date";
            os << "\n\n" << std::left;
            for (const auto &elem: dt.leaderboard) {
                os << std::left << std::setw(20) << elem->getNickname() << std::setw(20) <<
                   elem->getName() << std::setw(20) <<
                   elem->getTotalViewCount() << std::setw(20) << (elem->isStreaming() ? "Yes" : "No") << std::setw(20)
                   << (elem->isStreaming() ? std::to_string(elem->getCurrentStreamID()) : "-")
                   << std::setw(20) << elem->getBirthDate() <<
                   std::setw(20) << elem->getJoinDate() << "\n";
            }
            os << "\n";
        } else if constexpr (std::is_same_v<N, std::shared_ptr<Viewer>>) {
            os << "Viewer Leaderboard\n\n";
            os << std::left << std::setfill(' ') << std::setw(20) << "Nickname" << std::setw(20) << "Name"
               << std::setw(20) << "Watching a stream?" << std::setw(20) << "Stream ID"
               << std::setw(20) << "Birth Date" << std::setw(20) << "Join Date";
            os << "\n\n" << std::left;
            for (const auto &elem: dt.leaderboard) {
                os << std::left << std::setw(20) << elem->getNickname() << std::setw(20) <<
                   elem->getName() << std::setw(20) << (elem->isWatchingStream() ? "Yes" : "No") << std::setw(20)
                   << (elem->isWatchingStream() ? std::to_string((elem->getCurrentStream())->getUniqueId()) : "-")
                   << std::setw(20) <<
                   elem->getBirthDate() << std::setw(20) << elem->getJoinDate() << "\n";
            }
            os << "\n";
        } else if constexpr (std::is_same_v<N, std::shared_ptr<User>>) {
            os << "User Leaderboard\n\n";
            os << std::left << std::setfill(' ') << std::setw(20) << "Nickname" << std::setw(20) << "Name"
               << std::setw(20) << "User Type" << std::setw(20) << "Birth Date" << std::setw(20) << "Join Date";
            os << "\n\n" << std::left;
            for (const auto &elem: dt.leaderboard) {
                os << std::left << std::setw(20) << elem->getNickname() << std::setw(20) <<
                   elem->getName() << std::setw(20) <<
                   elem->getUserType() << std::setw(20) << std::setw(20) << elem->getBirthDate()
                   << std::setw(20) << elem->getJoinDate() << "\n";
            }
            os << "\n";
        } else if constexpr (std::is_same_v<N, std::shared_ptr<Stream>>) {
            os << "Stream Leaderboard\n\n";
            os << std::left << std::setfill(' ') << std::setw(20) << "Title" << std::setw(20) << "Language"
               << std::setw(20) << "Minimum Age" << std::setw(20) << "Genre" << std::setw(20) << "Type"
               << std::setw(20) << "Stream ID" << std::setw(20) << "Number of Viewers" << std::setw(20)
               << "Streamer Nickname" << std::setw(20) << "Stream Date" << std::setw(20) << "Num. Of Likes"
               << std::setw(20) << "Num. Of Dislikes";
            os << "\n\n" << std::left;
            for (const auto &elem: dt.leaderboard) {
                os << std::left << std::setw(20) << elem->getTitle() << std::setw(20) <<
                   elem->getLanguage() << std::setw(20) << elem->getMinAge() << std::setw(20) << elem->getGenre()
                   << std::setw(20)
                   << elem->getStreamType() << std::setw(20) << elem->getUniqueId() << std::setw(20)
                   << elem->getNumOfViewers() << std::setw(20) <<
                   elem->getStreamer()->getNickname() << std::setw(20) << elem->getStreamDate() << std::setw(20) <<
                   (elem->getVotes()).first << std::setw(20) << (elem->getVotes()).second << "\n";
            }
            os << "\n";
        }
        return os;
    }
    /**
     * Returns the leaderboard
     *
     * @return The current leaderboard
     */
    const std::vector<N> &get() const {
        return leaderboard;
    }

private:
    std::vector<N> leaderboard;
};
#endif //PROJECT_LEADERBOARD_H
