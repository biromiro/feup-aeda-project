//
// Created by Danny on 18/11/2020.
//

#ifndef PROJECT_INVALIDSTREAMBUILD_H
#define PROJECT_INVALIDSTREAMBUILD_H

#include <iostream>
#include <exception>

class InvalidStreamBuild : public std::runtime_error {
public:
    explicit InvalidStreamBuild(const std::string & message);
};

#endif //PROJECT_INVALIDSTREAMBUILD_H
