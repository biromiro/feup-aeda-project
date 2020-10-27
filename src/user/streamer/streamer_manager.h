//
// Created by biromiro on 27/10/20.
//

#ifndef PROJECT_STREAMER_MANAGER_H
#define PROJECT_STREAMER_MANAGER_H

#include "streamer.h"

class StreamerManager{
public:
    bool add(Streamer* streamer);
    bool remove(Streamer* streamer);
    bool has(Streamer* streamer) const;
    bool has(std::string nickname) const;
    Streamer* get(std::string nickname) const;
    void write(std::ostream os) const;
    void read(std::ostream os);

private:
    std::vector<Streamer*> streamers;
};


#endif //PROJECT_STREAMER_MANAGER_H
