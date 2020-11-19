//
// Created by Danny on 18/11/2020.
//

#ifndef PROJECT_INVALIDSTREAMTOADD_H
#define PROJECT_INVALIDSTREAMTOADD_H

#include <iostream>
#include <exception>
#include "../../model/stream/stream.h"

class InvalidStreamToAdd : public std::invalid_argument {
public:
    InvalidStreamToAdd(std::shared_ptr<Stream> stream, const std::string & message);

    const std::shared_ptr<Stream> &getStream() const;

private:
    std::shared_ptr<Stream> stream;
};

#endif //PROJECT_INVALIDSTREAMTOADD_H
