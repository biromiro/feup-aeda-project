//
// Created by biromiro on 18/10/20.
//

#include "../stream.h"
#include "../../user/viewer/viewer.h"
#include <vector>
#include <fstream>

#ifndef PROJECT_PRIVATESTREAM_H
#define PROJECT_PRIVATESTREAM_H

class Viewer;

class PrivateStream: public Stream {
public:
    PrivateStream();
    PrivateStream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamGenre genre, std::shared_ptr<Streamer> streamer);
    enum StreamType getStreamType() const override;
    std::vector<std::string> getWhitelist() const;
    unsigned int getMaxNumViewers() const;
    std::vector<std::string> getComments() const;
    bool addToWhitelist(std::shared_ptr<Viewer> v);
    bool setMaxNumViewers(unsigned int maxNumViewers);
    void addComment(const std::string& comment);
    bool canJoin(const std::shared_ptr<Viewer>& newViewer) const override;

    void readData(std::ifstream& ifs, std::shared_ptr<StreamerManager> streamerManager);

    void writeData(std::ofstream& ofs);
private:
    std::vector<std::string> whitelist;
    unsigned int maxNumViewers;
    std::vector<std::string> comments;
};

#endif //PROJECT_PRIVATESTREAM_H
