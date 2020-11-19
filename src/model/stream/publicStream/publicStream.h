//
// Created by biromiro on 18/10/20.
//

#include "../stream.h"


#ifndef PROJECT_PUBLICSTREAM_H


class PublicStream: public Stream {
public:
  
    /**
     * Default constructor of the PublicStream class
     *
     */
    PublicStream();

    /**
     * Constructor of the PublicStream class
     *
     * @param title title of the public stream
     * @param lang language the public stream is in
     * @param minAge minimum viewer age allowed
     * @param genre genre of the public stream
     * @param streamer streamer of the public stream
     */
    PublicStream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamGenre genre, std::shared_ptr<Streamer> streamer);

    /**
     * Getter of the public stream's type
     *
     * @return public stream's type
     */
    [[nodiscard]] enum StreamType getStreamType() const override;

    void readData(std::ifstream& ifs,const std::shared_ptr<StreamerManager>& streamerManager) override;

    void writeData(std::ofstream& ofs) override;
};


#define PROJECT_PUBLICSTREAM_H

#endif //PROJECT_PUBLICSTREAM_H
