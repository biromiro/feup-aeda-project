//
// Created by Danny on 24/12/2020.
//

#ifndef PROJECT_VIEWERALREADYORDERED_H
#define PROJECT_VIEWERALREADYORDERED_H

#include <iostream>
#include <exception>
#include "../orderLimitReached/orderLimitReached.h"

class ViewerAlreadyOrdered : public std::invalid_argument {
public:
    ViewerAlreadyOrdered(MerchRequest order, const std::string &message);
    MerchRequest getOrder() const;
private:
    MerchRequest order;
};

#endif //PROJECT_VIEWERALREADYORDERED_H
