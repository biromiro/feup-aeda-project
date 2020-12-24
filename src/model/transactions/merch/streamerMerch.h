//
// Created by nrtc on 20/12/2020.
//

#ifndef PROJECT_STREAMERMERCH_H
#define PROJECT_STREAMERMERCH_H

#include <queue>
#include "merchRequest.h"

class StreamerMerch {
public:
    StreamerMerch();

    /**
     * Constructor of the Streamer Merch class
     *
     * @param lim limit of the orders queue size
     */
    StreamerMerch(unsigned int lim);

    /**
     * Getter of the orders queue size limit
     *
     * @return limit of the orders queue size
     */
    unsigned int getLimit() const;

    /**
     * Getter of the orders queue
     *
     * @return orders queue
     */
    std::priority_queue<MerchRequest> getOrders() const;

    /**
     * Updates the orders queue size limit
     *
     * @param newLimit new orders queue size limit
     */
    void setLimit(unsigned int newLimit);

    /**
     * Processes the first order on the queue
     *
     * @return first order on the queue, now removed from it
     */
    MerchRequest processNextOrder();

    /**
     * Adds a new order to the orders queue
     *
     * @param newOrder order to add to the queue
     * @return true if order was successfully added, false otherwise
     */
    bool addOrder(MerchRequest newOrder);

    /**
     * Removes an order from the orders queue
     *
     * @param buyer name of the viewer whose order is to be removed
     * @return true if order was successfully removed, false otherwise
     */
    bool removeOrder(std::string buyer);
private:
    unsigned int limit;
    std::priority_queue<MerchRequest> orders;
};


#endif //PROJECT_STREAMERMERCH_H
