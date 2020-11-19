//
// Created by Danny on 18/11/2020.
//

#ifndef PROJECT_STREAMNOTFOUND_H
#define PROJECT_STREAMNOTFOUND_H

#include <iostream>
#include <exception>
#include "../../model/stream/stream.h"

class StreamNotFound : public std::invalid_argument {
public:
    StreamNotFound(std::shared_ptr<Stream> stream, const std::string & message);
    [[nodiscard]] const std::shared_ptr<Stream> &getStream() const;
private:
    std::shared_ptr<Stream> stream;
};


#endif //PROJECT_STREAMNOTFOUND_H
