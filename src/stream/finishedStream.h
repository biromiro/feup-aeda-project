//
// Created by Danny on 25/10/2020.
//

#ifndef PROJECT_FINISHEDSTREAM_H
#define PROJECT_FINISHEDSTREAM_H

class FinishedStream{
public:
    FinishedStream(unsigned int numOfViews);
    unsigned int getNumOfViews() const;
private:
    unsigned int numOfViews;
};

#endif //PROJECT_FINISHEDSTREAM_H
