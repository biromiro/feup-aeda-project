//
// Created by biromiro on 18/10/20.
//

#include <vector>
#include "memory"
#include "../user.h"
#include "../../stream/stream.h"


#ifndef PROJECT_STREAMER_H

class Stream;

class Streamer: public User{
public:
    /**
     * Constructor of the Streamer Class
     *
     * @param birthDate the birth date of the streamer
     * @param name the name of the streamer
     * @param nickname the nickname of the streamer
     */
    Streamer(Date birthDate, std::string name, std::string nickname);

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

private:
    std::vector<std::shared_ptr<Stream>> previousStreams;
    std::shared_ptr<Stream> currentStream;
    unsigned int totalViewCount;
};

#define PROJECT_STREAMER_H

#endif //PROJECT_STREAMER_H
