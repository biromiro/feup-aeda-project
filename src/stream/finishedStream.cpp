//
// Created by Danny on 25/10/2020.
//

#include "finishedStream.h"

FinishedStream::FinishedStream(unsigned int numOfViews) { this->numOfViews = numOfViews; }

unsigned int FinishedStream::getNumOfViews() const { return numOfViews; }
