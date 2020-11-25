//
// Created by Danny on 25/10/2020.
//

#ifndef PROJECT_FINISHEDSTREAM_H
#define PROJECT_FINISHEDSTREAM_H

#include "../stream.h"
#include <fstream>

/**
 * @file finishedStream.cpp
 *
 * @brief Class representing a finished stream object
 *
 * @ingroup stream
 */

/**
 * Implementation of the class finished stream
 *
 * A finished stream is an object, derived from stream, which saves data related to a previous live stream (either PUBLIC or PRIVATE)
 */
class FinishedStream: public Stream{
public:

   /**
    * Default constructor of the FinishedStream class
    *
    */
    FinishedStream();
    
    /**
     * Constructor of the FinishedStream class
     *
     * @param title title of the finished stream
     * @param lang language the finished stream is in
     * @param minAge minimum viewer age allowed
     * @param genre genre of the finished stream
     * @param streamer streamer of the finished stream
     * @param numOfViews number of views registered at the end of the stream that originated the finished stream
     */
    FinishedStream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamGenre genre, std::shared_ptr<Streamer> streamer, unsigned int numOfViews, unsigned int id, std::pair<unsigned int,unsigned int> oldVotes);

    /**
     * Getter of the number of views
     *
     * @return number of views
     */
    [[nodiscard]] unsigned int getNumOfViews() const;

    /**
     * Getter of the finished stream's type
     *
     * @return finished stream's type
     */
    [[nodiscard]] enum StreamType getStreamType() const override;

    /**
     * Loads finishedStreams from file and relates them to the respective streamer
     *
     * @param ifs File to read from
     * @param streamerManager streamerManager to update streamers with added streams
     * */
    void readData(std::ifstream& ifs, const std::shared_ptr<StreamerManager>& streamerManager) override;

    /**
     * Updates and saves to file the finishedStreams
     *
     * @param ofs File to save finishedStreams to
     * */
    void writeData(std::ofstream& ofs) override;

private:
    unsigned int numOfViews{};
};

#endif //PROJECT_FINISHEDSTREAM_H
