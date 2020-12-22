//
// Created by biromiro on 18/10/20.
//

#ifndef PROJECT_STREAMER_H
#define PROJECT_STREAMER_H

#include <vector>
#include "memory"
#include "../user.h"
#include "../../stream/stream.h"
#include "../../../exception/invalidAge/invalidAge.h"
#include "../../transactions/donations/donation.h"

class Stream;

/**
 * @file streamer.cpp
 *
 * @brief Class representing the Streamer class
 *
 * @ingroup user
 */

/**
 * Implementation of the Streamer class
 *
 * A streamer can start streams, finish them, and see his past streams and current stream statistics
 */
class Streamer: public User{
public:

    Streamer();
    /**
     * Constructor of the Streamer Class
     *
     * @param birthDate the birth date of the streamer
     * @param name the name of the streamer
     * @param nickname the nickname of the streamer
     */
    Streamer(Date birthDate, std::string name, std::string nickname, std::string password);

    /**
     * Checks whether or not the streamer is streaming
     *
     * @return True if the streamer is, in fact, streaming, false otherwise
     */
    [[nodiscard]] bool isStreaming() const;

    /**
     * Sets the stream
     *
     * @param stream the stream to be set to
     */
    void setStream(const std::shared_ptr<Stream>& stream);

    /**
     * Removes the current stream
     */
    void removeStream();

    /**
     * Increases the streamer's view count by given amount
     *
     * @param value number of views to add to total view count
     * */
    void addToViewCount(unsigned int value);

    /**
     * Getter of streamer's total view count
     *
     * @return the streamer's total view count
     * */
    [[nodiscard]] unsigned int getTotalViewCount() const;

    /**
     * Getter of streamer's current streamID
     *
     * @return the current stream's ID*/
    [[nodiscard]] unsigned int getCurrentStreamID() const;

    /**
     * Getter of streamer's past streamIDs
     *
     * @return vector of IDs of previous streams
     * */
    [[nodiscard]] const std::vector<unsigned int> &getPreviousStreamsIDs() const;

    /**
     * Reads streamer data from file
     *
     * @param ifs File to read streamers from
     * */
    void readData(std::ifstream& ifs) override;

    /**
     * Writes and updates streamer data to file
     *
     * @param ofs File to write streamers to
     * */
    void writeData(std::ofstream& ofs) override;

    /**
     * Overload of operator  < to streamers
     *
     * @param rhs given streamer to compare
     * @return self < given streamer
     * */
    bool operator<(const Streamer &rhs) const;

    /**
    * Overload of operator > to streamers
    *
    * @param rhs given streamer to compare
    * @return self > given streamer
     * */
    bool operator>(const Streamer &rhs) const;

    /**
    * Overload of operator <= to streamers
    *
    * @param rhs given streamer to compare
    * @return self <= given streamer
     * */
    bool operator<=(const Streamer &rhs) const;

    /**
    * Overload of operator == to streamers
    *
    * @param rhs given streamer to compare
    * @return self == given streamer
     * */
    bool operator==(const Streamer &rhs) const;

    /**
    * Overload of operator != to streamers
    *
    * @param rhs given streamer to compare
    * @return self != given streamer
     * */
    bool operator!=(const Streamer &rhs) const;

    /**
    * Overload of operator >= to streamers
    *
    * @param rhs given streamer to compare
    * @return self >= given streamer*/
    bool operator>=(const Streamer &rhs) const;

private:
    std::vector<unsigned int> previousStreamsIDs;
    unsigned int currentStreamID{};
    unsigned int totalViewCount{};
};

#endif //PROJECT_STREAMER_H
