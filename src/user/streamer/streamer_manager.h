//
// Created by biromiro on 27/10/20.
//

#ifndef PROJECT_STREAMER_MANAGER_H
#define PROJECT_STREAMER_MANAGER_H

#include "../../stream/streamManager.h"
#include "streamer.h"

class StreamerManager{
public:
    StreamerManager(StreamManager* streamManager,ViewerManager* viewerManager, UserManager* userManager);
    bool add(Streamer* streamer);
    bool addStream();
    bool remove(Streamer* streamer);
    bool startStream(Streamer* streamer, std::string title, StreamLanguage lang, unsigned int minAge, StreamType type);
    bool endStream(Streamer* streamer);
    bool has(Streamer* streamer) const;
    bool has(std::string nickname) const;
    Streamer* get(std::string nickname) const;
    void write(std::ostream os) const;
    void read(std::ostream os);

private:
    std::vector<Streamer*> streamers;
    StreamManager* streamManager;
    ViewerManager* viewerManager;
    UserManager* userManager;
};


#endif //PROJECT_STREAMER_MANAGER_H
