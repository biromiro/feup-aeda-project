//
// Created by Danny on 18/11/2020.
//

#ifndef PROJECT_STREAMALREADYFINISHED_H
#define PROJECT_STREAMALREADYFINISHED_H

#include <iostream>
#include <exception>
#include "../../model/stream/stream.h"

class StreamAlreadyFinished : public std::logic_error {
public:
    StreamAlreadyFinished(std::shared_ptr<Stream> stream, const std::string & message);

    [[nodiscard]] const std::shared_ptr<Stream> &getStream() const;

private:
    std::shared_ptr<Stream> stream;
};

#endif //PROJECT_STREAMALREADYFINISHED_H
