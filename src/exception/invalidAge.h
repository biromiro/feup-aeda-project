//
// Created by nrtc on 14/11/2020.
//

#ifndef PROJECT_INVALIDAGE_H
#define PROJECT_INVALIDAGE_H

#include <iostream>
#include <exception>

class InvalidAge : std::invalid_argument{
public:
    InvalidAge(unsigned int age, const std::string &message);
    const std::string& getMessage();
private:
    unsigned int age;
    std::string message;
};

#endif //PROJECT_INVALIDAGE_H
