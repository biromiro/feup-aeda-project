//
// Created by Danny on 18/11/2020.
//

#ifndef PROJECT_NOSTREAMWITHID_H
#define PROJECT_NOSTREAMWITHID_H

#include <iostream>
#include <exception>

class NoStreamWithID : public std::invalid_argument {
public:
    NoStreamWithID(unsigned int streamID, const std::string & message);
    [[nodiscard]] unsigned int getStreamId() const;

private:
    unsigned int streamID;
};

#endif //PROJECT_NOSTREAMWITHID_H
