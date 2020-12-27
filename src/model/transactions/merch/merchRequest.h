//
// Created by nrtc on 20/12/2020.
//

#ifndef PROJECT_MERCHREQUEST_H
#define PROJECT_MERCHREQUEST_H

#include <iostream>

class MerchRequest {
public:
    /**
     * Constructor of the Merch Request class
     *
     * @param buyer nickname of the viewer who is ordering merchandising
     * @param quantity quantity of merchandising ordered
     * @param purchaseA purchase availability of order
     */
    MerchRequest(std::string buyer, unsigned int quantity, unsigned int purchaseA);

    /**
     * Getter of the nickname of the viewer who made the order
     *
     * @return nickname of the viewer who made the order
     */
    const std::string &getBuyer() const;

    /**
     * Getter of the amount of merchandising ordered
     *
     * @return amount of merchandising ordered
     */
    unsigned int getQuantity() const;

    /**
     * Getter of the order's purchase availability
     *
     * @return order's purchase availability
     */
    unsigned int getPurchaseA() const;

    /**
     * Overload of operator < to merch requests
     *
     * @param mr given merch request to compare
     * @return self < given merch request
     */
    bool operator<(const MerchRequest &mr) const;

    friend std::ostream& operator<<(std::ostream& out, const MerchRequest& f);

    friend std::istream& operator>>(std::istream& out, MerchRequest& f);
private:
    std::string buyer;
    unsigned int quantity;
    unsigned int purchaseA;
};


#endif //PROJECT_MERCHREQUEST_H
