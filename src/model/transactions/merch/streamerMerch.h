//
// Created by nrtc on 20/12/2020.
//

#ifndef PROJECT_STREAMERMERCH_H
#define PROJECT_STREAMERMERCH_H

#include <queue>
#include "merchRequest.h"

/**
 * @file streamerMerch.cpp
 *
 * @brief Class representing the Streamer Merch class
 *
 * @ingroup transactions
 */

/**
 * Implementation of the Streamer Merch class
 *
 * Wrapper for the queue representing merch requests
 */
class StreamerMerch {
public:
    StreamerMerch();

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
    bool addOrder(const MerchRequest& newOrder);

    /**
     * Removes an order from the orders queue
     *
     * @param buyer nickname of the viewer whose order is to be removed
     * @return true if order was successfully removed, false otherwise
     */
    bool removeOrder(std::string buyer);

    /**
     * Output stream operator overload
     *
     * @param out the stream to output
     * @param f the streamer merch object to output
     * @return the stream passed as parameter
     */
    friend std::ostream& operator<<(std::ostream& out, const StreamerMerch& f);

    /**
     * Input stream operator overload
     *
     * @param out the stream to get input from
     * @param f the streamer merch object to get input
     * @return the stream passed as parameter
     */
    friend std::istream& operator>>(std::istream& out, StreamerMerch& f);
private:
    unsigned int limit;
    std::priority_queue<MerchRequest> orders;
};



#endif //PROJECT_STREAMERMERCH_H
