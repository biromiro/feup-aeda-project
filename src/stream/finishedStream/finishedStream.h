//
// Created by Danny on 25/10/2020.
//

#ifndef PROJECT_FINISHEDSTREAM_H
#define PROJECT_FINISHEDSTREAM_H

#include "../stream.h"
#include <fstream>

class FinishedStream: public Stream{
public:
    FinishedStream();
    FinishedStream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamGenre genre, std::shared_ptr<Streamer> streamer, unsigned int numOfViews);
    unsigned int getNumOfViews() const;
    enum StreamType getStreamType() const override;

    void readData(std::ifstream& ifs, std::shared_ptr<StreamerManager> streamerManager);

    void writeData(std::ofstream& ofs);

private:
    unsigned int numOfViews;
};

#endif //PROJECT_FINISHEDSTREAM_H
