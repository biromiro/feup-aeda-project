//
// Created by nrtc on 20/12/2020.
//

#include "merchRequest.h"
#include "../../../exception/invalidPurchaseAvailability/invalidPurchaseAvailability.h"

MerchRequest::MerchRequest(std::string buyer, unsigned int quantity, unsigned int purchaseA): buyer(buyer), quantity(quantity) {
    if (purchaseA < 1 || purchaseA > 5) { throw InvalidPurchaseAvailability(purchaseA, "Purchase availability must be between 1 and 5!"); }
    else { this->purchaseA = purchaseA; }
}

const std::string &MerchRequest::getBuyer() const {
    return buyer;
}

unsigned int MerchRequest::getQuantity() const {
    return quantity;
}

unsigned int MerchRequest::getPurchaseA() const {
    return purchaseA;
}

bool MerchRequest::operator<(const MerchRequest &mr) const {
    if (quantity > mr.quantity) { return true; }
    else if (quantity < mr.quantity) { return false; }
    else {
        return purchaseA < mr.purchaseA;
    }
}

std::ostream &operator<<(std::ostream &out, const MerchRequest &f) {
    out << f.quantity << "\n";
    out << f.buyer << "\n";
    out << f.purchaseA << "\n";
    return out;
}

std::istream &operator>>(std::istream &in, MerchRequest &f) {
    getline(in, f.buyer);
    in.ignore();
    in >> f.quantity;
    in >> f.purchaseA;
    return in;
}
