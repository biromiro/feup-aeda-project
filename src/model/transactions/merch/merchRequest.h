//
// Created by nrtc on 20/12/2020.
//

#ifndef PROJECT_MERCHREQUEST_H
#define PROJECT_MERCHREQUEST_H

#include <iostream>

/**
 * @file merchRequest.cpp
 *
 * @brief Class representing the Merch Request class
 *
 * @ingroup transactions
 */

/**
 * Implementation of the merch request class
 *
 * Represents a merch request, with its buyer, number of items ordered and availability
 */
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

    /**
     * Output stream operator overload
     *
     * @param out the stream to output
     * @param f the merch request to output
     * @return the stream passed as parameter
     */
    friend std::ostream& operator<<(std::ostream& out, const MerchRequest& f);

    /**
     * Input stream operator overload
     *
     * @param out the stream to get input from
     * @param f the merch request to get input
     * @return the stream passed as parameter
     */
    friend std::istream& operator>>(std::istream& out, MerchRequest& f);
private:
    std::string buyer;
    unsigned int quantity;
    unsigned int purchaseA;
};


#endif //PROJECT_MERCHREQUEST_H
