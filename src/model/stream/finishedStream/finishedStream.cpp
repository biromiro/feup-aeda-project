//
// Created by Danny on 25/10/2020.
//

#include "finishedStream.h"

FinishedStream::FinishedStream() : Stream(StreamType::FINISHED){}

FinishedStream::FinishedStream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamGenre genre,
                               std::shared_ptr<Streamer> streamer, unsigned int numOfViews): Stream(title,lang,minAge,StreamType::FINISHED,genre,streamer), numOfViews(numOfViews){

}


enum StreamType FinishedStream::getStreamType() const { return type; }

unsigned int FinishedStream::getNumOfViews() const { return numOfViews; }

void FinishedStream::readData(std::ifstream &ifs, std::shared_ptr<StreamerManager> streamerManager) {
    ifs >> numOfViews;
    Stream::readData(ifs, streamerManager);
}

void FinishedStream::writeData(std::ofstream &ofs) {
    ofs << numOfViews;
    Stream::writeData(ofs);
}

