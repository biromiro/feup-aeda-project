//
// Created by biromiro on 18/10/20.
//

#include "../stream.h"


#ifndef PROJECT_PUBLICSTREAM_H

/**
 * @file publicStream.cpp
 *
 * @brief Class representing a public stream object
 *
 * @ingroup stream
 */

/**
 * Implementation of the class public stream
 *
 * A public stream is an object, derived from stream, representing a more general, up and running, stream, on the given platform
 */
class PublicStream: public Stream {
public:
  
    /**
     * Default constructor of the PublicStream class
     *
     */
    PublicStream();

    /**
     * Constructor of the PublicStream class
     *
     * @param title title of the public stream
     * @param lang language the public stream is in
     * @param minAge minimum viewer age allowed
     * @param genre genre of the public stream
     * @param streamer streamer of the public stream
     */
    PublicStream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamGenre genre, std::shared_ptr<Streamer> streamer);

    /**
     * Getter of the public stream's type
     *
     * @return public stream's type
     */
    [[nodiscard]] enum StreamType getStreamType() const override;

    /**
    * Loads publicStreams from file and relates them to the respective streamer
    *
    * @param ifs File to read from
    * @param streamerManager streamerManager to update streamers with added streams
     * */
    void readData(std::ifstream& ifs,const std::shared_ptr<StreamerManager>& streamerManager) override;

    /**
     * Updates and saves to file the publicStreams
    *
     * @param ofs File to save publicStreams to
    * */
    void writeData(std::ofstream& ofs) override;
};


#define PROJECT_PUBLICSTREAM_H

#endif //PROJECT_PUBLICSTREAM_H
