//
// Created by nrtc on 20/12/2020.
//

#ifndef PROJECT_MERCHREQUEST_H
#define PROJECT_MERCHREQUEST_H

#include <iostream>

class MerchRequest {
public:
    MerchRequest(std::string buyer, unsigned int quantity, unsigned int purchaseA);
    const std::string &getBuyer() const;
    unsigned int getQuantity() const;
    unsigned int getPurchaseA() const;
    bool operator<(const MerchRequest &mr) const;
private:
    std::string buyer;
    unsigned int quantity;
    unsigned int purchaseA;
};


#endif //PROJECT_MERCHREQUEST_H
