//
// Created by Danny on 18/11/2020.
//

#ifndef PROJECT_NOSTREAMWITHID_H
#define PROJECT_NOSTREAMWITHID_H

#include <iostream>
#include <exception>

class NoStreamWithID : std::invalid_argument {
public:
    NoStreamWithID(unsigned int streamID, const std::string & message);
    const std::string & getMessage();
private:
    unsigned int streamID;
    std::string message;
};

#endif //PROJECT_NOSTREAMWITHID_H
