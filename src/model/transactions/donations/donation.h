//
// Created by nrtc on 20/12/2020.
//

#ifndef PROJECT_DONATION_H
#define PROJECT_DONATION_H

#include <iostream>

/**
 * @file donation.cpp
 *
 * @brief Class representing the donation class
 *
 * @ingroup transactions
 */


/**
 * Enum class representing the rating given to a streamer
 */
enum class streamerWorkRating{
    VERY_BAD, BAD, MEH, GOOD, VERY_GOOD
};


/**
 * Implementation of the donation class
 *
 * Represents a donation, with its receiver, ammount and rating
 */
class Donation {
public:

    /**
     * Donation constructor
     *
     * @param nickname the nickname of the streamer to donate to
     * @param ammount the ammount donated
     * @param rating the rating given to the streamer
     */
    Donation(std::string nickname, float ammount, streamerWorkRating rating);

    /**
     * Getter of the given rating in the donation
     *
     * @return the rating given
     */
    [[nodiscard]] streamerWorkRating getRating() const;


    /**
     * Getter of the ammount donated
     *
     * @return the ammount donated
     */
    [[nodiscard]] float getAmmount() const;

    /**
     * Getter of the donated streamer nickname
     *
     * @return the nickname of the donated streamer
     */
    [[nodiscard]] const std::string &getStreamerNickname() const;

    /**
     * Operator < of the class Donation
     *
     * @param rhs the donation to compare to
     * @return True if smaller, false otherwise
     */
    bool operator<(const Donation &rhs) const;

    /**
     * Output stream operator overload
     *
     * @param out the stream to output
     * @param f the donation to output
     * @return the stream passed as parameter
     */
    friend std::ostream& operator<<(std::ostream& out, const Donation& f);

    /**
     * Input stream operator overload
     *
     * @param out the stream to get input from
     * @param f the donation to get input
     * @return the stream passed as parameter
     */
    friend std::istream& operator>>(std::istream& out, Donation& f);

private:
    streamerWorkRating rating;
    float ammount;
    std::string streamerNickname;
};

/**
 * Output stream operator for the streamerWorkRating enum
 *
 * @param out the stream to output
 * @param f the streamWorkRating to output
 * @return the stream passed as parameter
 */
std::ostream& operator<<(std::ostream& out, const streamerWorkRating& f);

/**
 * Input stream operator for the streamerWorkRating enum
 *
 * @param out the stream to get input from
 * @param f the streamWorkRating to get input
 * @return the stream passed as parameter
 */
std::istream& operator>>(std::istream& out, streamerWorkRating& f);
#endif //PROJECT_DONATION_H
