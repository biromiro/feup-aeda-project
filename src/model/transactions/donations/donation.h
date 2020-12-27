//
// Created by nrtc on 20/12/2020.
//

#ifndef PROJECT_DONATION_H
#define PROJECT_DONATION_H

#include <iostream>

enum class streamerWorkRating{
    VERY_BAD, BAD, MEH, GOOD, VERY_GOOD
};

class Donation {
public:
    Donation(std::string nickname, float ammount, streamerWorkRating rating);

    [[nodiscard]] streamerWorkRating getRating() const;

    [[nodiscard]] float getAmmount() const;

    [[nodiscard]] const std::string &getStreamerNickname() const;

    bool operator<(const Donation &rhs) const;

private:
    streamerWorkRating rating;
    float ammount;
    std::string streamerNickname;
};

std::ostream& operator<<(std::ostream& out, const streamerWorkRating& f);
std::istream& operator>>(std::istream& out, streamerWorkRating& f);
#endif //PROJECT_DONATION_H
