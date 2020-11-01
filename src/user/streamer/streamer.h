//
// Created by biromiro on 18/10/20.
//

#include <vector>
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
     * Getter of the type of User
     *
     * @return the user's type (in this case, STREAMER)
     */
    enum UserTypes getUserType() const override;

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
    void setStream(Stream* stream);

    /**
     * Removes the current stream
     */
    void removeStream();

private:
    std::vector<Stream*> previousStreams;
    Stream* currentStream;
    unsigned int totalViewCount;
};

#define PROJECT_STREAMER_H

#endif //PROJECT_STREAMER_H
