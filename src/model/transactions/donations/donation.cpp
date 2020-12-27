//
// Created by nrtc on 20/12/2020.
//

#include <map>
#include "donation.h"

streamerWorkRating Donation::getRating() const {
    return rating;
}

float Donation::getAmmount() const {
    return ammount;
}

const std::string &Donation::getStreamerNickname() const {
    return streamerNickname;
}

Donation::Donation(std::string nickname, float ammount, streamerWorkRating rating):
                    streamerNickname(std::move(nickname)), ammount(ammount), rating(rating){
}

bool Donation::operator<(const Donation &rhs) const {
    if (ammount < rhs.ammount)
        return true;
    if (rhs.ammount < ammount)
        return false;
    if (rating < rhs.rating)
        return true;
    if (rating > rhs.rating)
        return false;
    return streamerNickname < rhs.streamerNickname;
}

std::ostream &operator<<(std::ostream &out, const Donation &f) {
    out << f.ammount << "\n";
    out << f.streamerNickname << "\n";
    out << f.rating << "\n";
    return out;
}

std::istream &operator>>(std::istream &in, Donation &f) {
    in >> f.ammount;
    in.ignore();
    getline(in, f.streamerNickname);
    in >> f.rating;
    return in;
}

std::ostream& operator<<(std::ostream& out, const streamerWorkRating& f){
    std::map<streamerWorkRating,std::string> map = {{streamerWorkRating::VERY_BAD, "Very Bad"},
                                                    {streamerWorkRating::BAD, "Bad"},
                                                    {streamerWorkRating::MEH, "Meh"},
                                                    {streamerWorkRating::GOOD, "Good"},
                                                    {streamerWorkRating::VERY_GOOD, "Very Good"}};

    out << map[f];
    return out;
}

std::istream& operator>>(std::istream& out, streamerWorkRating& f){
    std::string temp;
    std::map<std::string, streamerWorkRating> map = {{ "Very Bad", streamerWorkRating::VERY_BAD,},
                                                    {"Bad", streamerWorkRating::BAD},
                                                    {"Meh", streamerWorkRating::MEH},
                                                    {"Good", streamerWorkRating::GOOD},
                                                    {"Very Good", streamerWorkRating::VERY_GOOD}};

    getline(out, temp);
    f = map[temp];
    return out;
}