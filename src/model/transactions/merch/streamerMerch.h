//
// Created by nrtc on 20/12/2020.
//

#ifndef PROJECT_STREAMERMERCH_H
#define PROJECT_STREAMERMERCH_H

#include <queue>
#include "merchRequest.h"

class StreamerMerch {
public:
    StreamerMerch(unsigned int lim);
    unsigned int getLimit() const;
    void setLimit(unsigned int newLimit);
    MerchRequest processNextOrder();
    bool addOrder(MerchRequest newOrder);
    bool removeOrder(std::string buyer);
private:
    unsigned int limit;
    std::priority_queue<MerchRequest> orders;
};


#endif //PROJECT_STREAMERMERCH_H
