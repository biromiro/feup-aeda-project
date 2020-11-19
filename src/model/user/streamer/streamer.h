//
// Created by biromiro on 18/10/20.
//

#include <vector>
#include "memory"
#include "../user.h"
#include "../../stream/stream.h"
#include "../../../exception/invalidAge/invalidAge.h"


#ifndef PROJECT_STREAMER_H

class Stream;

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
    bool isStreaming();

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

    void addToViewCount(unsigned int value);

    unsigned int getTotalViewCount() const;

    unsigned int getCurrentStreamID() const;

    const std::vector<unsigned int> &getPreviousStreamsIDs() const;

    void readData(std::ifstream& ifs);

    void writeData(std::ofstream& ofs);

    bool operator<(const Streamer &rhs) const;
    bool operator>(const Streamer &rhs) const;
    bool operator<=(const Streamer &rhs) const;
    bool operator==(const Streamer &rhs) const;
    bool operator!=(const Streamer &rhs) const;
    bool operator>=(const Streamer &rhs) const;

private:
    std::vector<unsigned int> previousStreamsIDs;
    unsigned int currentStreamID;
    unsigned int totalViewCount;
};

#define PROJECT_STREAMER_H

#endif //PROJECT_STREAMER_H
