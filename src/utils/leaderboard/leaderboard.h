//
// Created by biromiro on 01/11/WIDTH.
//

#ifndef PROJECT_LEADERBOARD_H
#define PROJECT_LEADERBOARD_H

#include <iostream>
#include <vector>
#include <memory>
#include<type_traits>
#include "../../model/stream/stream.h"
#include "../otherFunctions/auxiliaryFunctions.h"
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
    explicit Leaderboard(const std::vector<N>& vec): leaderboard(vec){};

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
            os << std::left << std::setfill(' ') << std::setw(WIDTH) << "Nickname" << std::setw(WIDTH) << "Name"
               << std::setw(WIDTH) << "View Count" << std::setw(WIDTH) << "Streaming?" << std::setw(WIDTH) << "Stream ID"
               << std::setw(WIDTH) << "Birth Date" << std::setw(WIDTH) << "Join Date";
            os << "\n\n" << std::left;
            for (const auto &elem: dt.leaderboard) {
                os << std::left << std::setw(WIDTH) << shrinkToColumnSize(elem->getNickname()) << std::setw(WIDTH) <<
                shrinkToColumnSize(elem->getName()) << std::setw(WIDTH) <<
                   elem->getTotalViewCount() << std::setw(WIDTH) << (elem->isStreaming() ? "Yes" : "No") << std::setw(WIDTH)
                   << (elem->isStreaming() ? std::to_string(elem->getCurrentStreamID()) : "-")
                   << std::setw(WIDTH) << elem->getBirthDate() <<
                   std::setw(WIDTH) << elem->getJoinDate() << "\n";
            }
            os << "\n";
        } else if constexpr (std::is_same_v<N, std::shared_ptr<Viewer>>) {
            os << "Viewer Leaderboard\n\n";
            os << std::left << std::setfill(' ') << std::setw(WIDTH) << "Nickname" << std::setw(WIDTH) << "Name"
               << std::setw(WIDTH) << "Watching" << std::setw(WIDTH) << "Stream ID"
               << std::setw(WIDTH) << "Birth Date" << std::setw(WIDTH) << "Join Date";
            os << "\n\n" << std::left;
            for (const auto &elem: dt.leaderboard) {
                os << std::left << std::setw(WIDTH) << shrinkToColumnSize(elem->getNickname()) << std::setw(WIDTH) <<
                shrinkToColumnSize(elem->getName()) << std::setw(WIDTH) << (elem->isWatchingStream() ? "Yes" : "No") << std::setw(WIDTH)
                   << (elem->isWatchingStream() ? std::to_string((elem->getCurrentStream())->getUniqueId()) : "-")
                   << std::setw(WIDTH) <<
                   elem->getBirthDate() << std::setw(WIDTH) << elem->getJoinDate() << "\n";
            }
            os << "\n";
        } else if constexpr (std::is_same_v<N, std::shared_ptr<User>>) {
            os << "User Leaderboard\n\n";
            os << std::left << std::setfill(' ') << std::setw(WIDTH) << "Nickname" << std::setw(WIDTH) << "Name"
               << std::setw(WIDTH) << "User Type" << std::setw(WIDTH) << "Birth Date" << std::setw(WIDTH) << "Join Date";
            os << "\n\n" << std::left;
            for (const auto &elem: dt.leaderboard) {
                os << std::left << std::setw(WIDTH) << shrinkToColumnSize(elem->getNickname()) << std::setw(WIDTH) <<
                shrinkToColumnSize(elem->getName()) << std::setw(WIDTH) <<
                   elem->getUserType() << std::setw(WIDTH) << std::setw(WIDTH) << elem->getBirthDate()
                   << std::setw(WIDTH) << elem->getJoinDate() << "\n";
            }
            os << "\n";
        } else if constexpr (std::is_same_v<N, std::shared_ptr<Stream>>) {
            os << "Stream Leaderboard\n\n";
            os << std::left << std::setfill(' ') << std::setw(WIDTH) << "Title" << std::setw(WIDTH) << "Language"
               << std::setw(WIDTH) << "Minimum Age" << std::setw(WIDTH) << "Genre" << std::setw(WIDTH) << "Type"
               << std::setw(WIDTH) << "Stream ID" << std::setw(WIDTH) << "Num. Viewers" << std::setw(WIDTH)
               << "Streamer Nick" << std::setw(WIDTH) << "Stream Date" << std::setw(WIDTH) << "Num. Likes"
               << std::setw(WIDTH) << "Num. Dislikes";
            os << "\n\n" << std::left;
            for (const auto &elem: dt.leaderboard) {
                os << std::left << std::setw(WIDTH) << shrinkToColumnSize(elem->getTitle()) << std::setw(WIDTH) <<
                   elem->getLanguage() << std::setw(WIDTH) << elem->getMinAge() << std::setw(WIDTH) << elem->getGenre()
                   << std::setw(WIDTH)
                   << elem->getStreamType() << std::setw(WIDTH) << elem->getUniqueId() << std::setw(WIDTH)
                   << elem->getNumOfViewers() << std::setw(WIDTH) <<
                   elem->getStreamer()->getNickname() << std::setw(WIDTH) << elem->getStreamDate() << std::setw(WIDTH) <<
                   (elem->getVotes()).first << std::setw(WIDTH) << (elem->getVotes()).second << "\n";
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
