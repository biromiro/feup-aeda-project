//
// Created by nrtc on 14/11/2020.
//

#ifndef PROJECT_INVALIDAGE_H
#define PROJECT_INVALIDAGE_H

#include <iostream>
#include <exception>

class InvalidAge : public std::invalid_argument{
public:
    InvalidAge(unsigned int age, const std::string &message);

    unsigned int getAge() const;

private:
    unsigned int age;
};

#endif //PROJECT_INVALIDAGE_H
