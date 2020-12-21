//
// Created by Danny on 21/12/2020.
//

#ifndef PROJECT_ORDERLIMITREACHED_H
#define PROJECT_ORDERLIMITREACHED_H

#include <iostream>
#include <exception>
#include "../../model/transactions/merch/merchRequest.h"

class OrderLimitReached : public std::length_error {
public:
    OrderLimitReached(MerchRequest failedOrder, const std::string &message);
    [[nodiscard]] MerchRequest getOrder() const;
private:
    MerchRequest order;
};

#endif //PROJECT_ORDERLIMITREACHED_H
