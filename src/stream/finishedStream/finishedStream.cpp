//
// Created by Danny on 25/10/2020.
//

#include "finishedStream.h"

FinishedStream::FinishedStream(std::string title, enum StreamLanguage lang, unsigned int minAge,
                               std::shared_ptr<Streamer> streamer, unsigned int numOfViews): Stream(title,lang,minAge,FINISHED,streamer), numOfViews(numOfViews){

}


enum StreamType FinishedStream::getStreamType() const { return type; }

unsigned int FinishedStream::getNumOfViews() const { return numOfViews; }

