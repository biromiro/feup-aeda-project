//
// Created by nrtc on 20/12/2020.
//

#include "streamerMerch.h"
#include "../../../exception/orderLimitReached/orderLimitReached.h"
#include "../../../exception/orderNotFound/orderNotFound.h"
#include "../../../exception/viewerAlreadyOrdered/viewerAlreadyOrdered.h"
#include "../../../exception/noOrderToProcess/noOrderToProcess.h"

StreamerMerch::StreamerMerch() {
    limit = 0;
    orders = std::priority_queue<MerchRequest>();
}

unsigned int StreamerMerch::getLimit() const { return limit; }

std::priority_queue<MerchRequest> StreamerMerch::getOrders() const { return orders; }

void StreamerMerch::setLimit(unsigned int newLimit) {
    if (newLimit < limit) {
        unsigned int counter = newLimit;
        std::priority_queue<MerchRequest> temp;
        while (counter != 0 && !orders.empty()) {
            temp.push(orders.top());
            orders.pop();
            counter--;
        }
        orders = temp;
    }
    limit = newLimit;
}

MerchRequest StreamerMerch::processNextOrder() {
    if(orders.empty()) throw NoOrderToProcess("You have no orders to process!");
    MerchRequest nextOrder = orders.top();
    orders.pop();
    return nextOrder;
}

bool StreamerMerch::addOrder(const MerchRequest& newOrder) {
    auto temp = orders;
    bool foundName = false;
    while (!temp.empty()) {
        auto item = temp.top();
        temp.pop();
        if (item.getBuyer() == newOrder.getBuyer()) {
            foundName = true;
            break;
        }
    }
    if (foundName) { throw ViewerAlreadyOrdered(newOrder, "You already have an order awaiting processing!"); }
    if (orders.size() < limit) {
        orders.push(newOrder);
        return true;
    }
    else { throw OrderLimitReached(newOrder, "The limit for orders of this streamer was already reached!"); }
}

bool StreamerMerch::removeOrder(std::string buyer) {
    bool found = false;
    std::priority_queue<MerchRequest> temp;
    while (!orders.empty()) {
        auto item = orders.top();
        orders.pop();
        if (item.getBuyer() == buyer) {
            found = true;
            continue;
        }
        temp.push(item);
    }
    orders = temp;
    if (found) { return true; }
    else { throw OrderNotFound(buyer, "There's no order under your name!"); }
}

std::ostream &operator<<(std::ostream &out, const StreamerMerch &f) {
    out << f.limit << "\n";
    out << f.orders.size() << "\n";
    auto orderTmp = f.orders;
    while(!orderTmp.empty()){
        out << orderTmp.top();
        orderTmp.pop();
    }
    return out;
}

std::istream &operator>>(std::istream &in, StreamerMerch &f) {
    in >> f.limit;
    unsigned int size;
    MerchRequest order("",0,1);
    in >> size;
    while(size--){
        in >> order;
        f.orders.push(order);
    }
    return in;
}

