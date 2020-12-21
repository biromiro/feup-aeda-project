//
// Created by Danny on 21/12/2020.
//

#ifndef PROJECT_INVALIDPURCHASEAVAILABILITY_H
#define PROJECT_INVALIDPURCHASEAVAILABILITY_H

#include <iostream>
#include <exception>

class InvalidPurchaseAvailability : public std::invalid_argument {
public:
    InvalidPurchaseAvailability(unsigned int purchaseA, const std::string &message);
    unsigned int getPurchaseA() const;
private:
    unsigned int purchaseA;
};

#endif //PROJECT_INVALIDPURCHASEAVAILABILITY_H
