//
// Created by biromiro on 18/10/20.
//

#include "../stream.h"

#ifndef PROJECT_PRIVATESTREAM_H

class PrivateStream: public Stream {
public:
    PrivateStream(std::string title, std::string lang, unsigned minAge);
};


#define PROJECT_PRIVATESTREAM_H

#endif //PROJECT_PRIVATESTREAM_H
