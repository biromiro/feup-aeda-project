//
// Created by Danny on 21/12/2020.
//

#ifndef PROJECT_ORDERNOTFOUND_H
#define PROJECT_ORDERNOTFOUND_H

#include <iostream>
#include <exception>

class OrderNotFound : public std::invalid_argument {
public:
    OrderNotFound(std::string buyer, const std::string &message);
    [[nodiscard]] std::string getBuyer() const;
private:
    std::string buyer;
};

#endif //PROJECT_ORDERNOTFOUND_H
