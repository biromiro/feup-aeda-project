//
// Created by Danny on 18/11/2020.
//

#ifndef PROJECT_INVALIDSTREAMBUILD_H
#define PROJECT_INVALIDSTREAMBUILD_H

#include <iostream>
#include <exception>

class InvalidStreamBuild : std::invalid_argument {
public:
    InvalidStreamBuild(const std::string & message);
    const std::string & getMessage();
private:
    std::string message;
};

#endif //PROJECT_INVALIDSTREAMBUILD_H
