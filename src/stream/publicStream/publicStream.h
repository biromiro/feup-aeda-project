//
// Created by biromiro on 18/10/20.
//

#include "../stream.h"

#ifndef PROJECT_PUBLICSTREAM_H


class PublicStream: public Stream {
public:
    PublicStream(std::string title, std::string lang, unsigned int minAge);
    enum StreamType getStreamType() const override;
};


#define PROJECT_PUBLICSTREAM_H

#endif //PROJECT_PUBLICSTREAM_H
