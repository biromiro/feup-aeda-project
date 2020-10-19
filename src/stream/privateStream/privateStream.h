//
// Created by biromiro on 18/10/20.
//

#include "../stream.h"
#include <vector>

#ifndef PROJECT_PRIVATESTREAM_H

class PrivateStream: public Stream {
public:
    PrivateStream(std::string title, std::string lang, size_t minAge);
    enum StreamType getStreamType() const override;
    void getComment(std::string comment);
private:
    std::vector<std::string> comments;
};


#define PROJECT_PRIVATESTREAM_H

#endif //PROJECT_PRIVATESTREAM_H
