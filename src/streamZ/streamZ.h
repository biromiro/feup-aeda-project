//
// Created by biromiro on 13/10/20.
//

//#include "../stream/privateStream/privateStream.h"
//#include "../stream/publicStream/publicStream.h"
#include "../user/streamer/streamer.h"
#include "../stream/stream.h"
#include "../user/user.h"
#include <vector>
#include <string>

#ifndef PROJECT_STREAMZ_H
#define PROJECT_STREAMZ_H
class StreamZ{
private:
    std::vector<Stream*> activeStreams;
    std::vector<User*>  allUsers;
public:
    StreamZ();
    void filterAge(unsigned int minAge);
    void filterLanguage(std::string streamLang);
    void sortByViews(int order);
    void showActiveStreams();
};

#endif //PROJECT_STREAMZ_H
