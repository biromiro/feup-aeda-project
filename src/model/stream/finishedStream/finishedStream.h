//
// Created by Danny on 25/10/2020.
//

#ifndef PROJECT_FINISHEDSTREAM_H
#define PROJECT_FINISHEDSTREAM_H

#include "../stream.h"
#include <fstream>

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
    FinishedStream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamGenre genre, std::shared_ptr<Streamer> streamer, unsigned int numOfViews, unsigned int id);

    /**
     * Getter of the number of views
     *
     * @return number of views
     */
    unsigned int getNumOfViews() const;

    /**
     * Getter of the finished stream's type
     *
     * @return finished stream's type
     */
    enum StreamType getStreamType() const override;

    /**
     * Getter of the ID the stream had when active
     *
     * @return ID the stream had when active
     */
    unsigned int getID() const;

    void readData(std::ifstream& ifs, std::shared_ptr<StreamerManager> streamerManager);

    void writeData(std::ofstream& ofs);

private:
    unsigned int numOfViews;
    unsigned int id;
};

#endif //PROJECT_FINISHEDSTREAM_H
