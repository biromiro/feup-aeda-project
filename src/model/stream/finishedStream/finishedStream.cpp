//
// Created by Danny on 25/10/2020.
//

#include "finishedStream.h"

FinishedStream::FinishedStream() : Stream(StreamType::FINISHED){}

FinishedStream::FinishedStream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamGenre genre,
                               std::shared_ptr<Streamer> streamer, unsigned int numOfViews, unsigned int id, std::pair<unsigned int,unsigned int> oldVotes): Stream(std::move(title),lang,minAge,StreamType::FINISHED,genre,std::move(streamer)), numOfViews(numOfViews){
    uniqueID = id;
    numOfViewers = numOfViews;
    votingSystem = oldVotes;
}

enum StreamType FinishedStream::getStreamType() const { return type; }

unsigned int FinishedStream::getNumOfViews() const { return numOfViews; }

void FinishedStream::readData(std::ifstream &ifs, const std::shared_ptr<StreamerManager>& streamerManager) {
    ifs >> numOfViews;
    Stream::readData(ifs, streamerManager);
}

void FinishedStream::writeData(std::ofstream &ofs) {
    ofs << numOfViews << "\n";
    Stream::writeData(ofs);
}

