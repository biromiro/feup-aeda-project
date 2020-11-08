//
// Created by biromiro on 18/10/20.
//

#include "../stream.h"


#ifndef PROJECT_PUBLICSTREAM_H


class PublicStream: public Stream {
public:
    PublicStream();

    PublicStream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamGenre genre, std::shared_ptr<Streamer> streamer);
    enum StreamType getStreamType() const override;

    void readData(std::ifstream& ifs,std::shared_ptr<StreamerManager> streamerManager);

    void writeData(std::ofstream& ofs);
};


#define PROJECT_PUBLICSTREAM_H

#endif //PROJECT_PUBLICSTREAM_H
