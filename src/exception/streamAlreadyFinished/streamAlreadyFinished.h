//
// Created by Danny on 18/11/2020.
//

#ifndef PROJECT_STREAMALREADYFINISHED_H
#define PROJECT_STREAMALREADYFINISHED_H

#include <iostream>
#include <exception>
#include "../../model/stream/stream.h"

class StreamAlreadyFinished : std::invalid_argument {
public:
    StreamAlreadyFinished(std::shared_ptr<Stream> stream, const std::string & message);
    const std::string & getMessage();
private:
    std::shared_ptr<Stream> stream;
    std::string message;
};

#endif //PROJECT_STREAMALREADYFINISHED_H
