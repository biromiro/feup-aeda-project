//
// Created by Danny on 25/10/2020.
//

#ifndef PROJECT_FINISHEDSTREAM_H
#define PROJECT_FINISHEDSTREAM_H

#include "../stream.h"

class FinishedStream: public Stream{
public:
    FinishedStream(std::string title, enum StreamLanguage lang, unsigned int minAge, std::shared_ptr<Streamer> streamer, unsigned int numOfViews);
    unsigned int getNumOfViews() const;
    enum StreamType getStreamType() const override;
private:
    unsigned int numOfViews;
};

#endif //PROJECT_FINISHEDSTREAM_H
