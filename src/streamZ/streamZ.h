//
// Created by biromiro on 13/10/20.
//

//#include "../stream/privateStream/privateStream.h"
//#include "../stream/publicStream/publicStream.h"
#include "../user/viewer/viewer_manager.h"
#include "../user/streamer/streamer_manager.h"
#include "../user/admin/admin_manager.h"
#include "../user/user_manager.h"
#include "../stream/streamManager.h"
#include "../utils/leaderboard/leaderboard_manager.h"
#include <vector>
#include <string>

#ifndef PROJECT_STREAMZ_H
#define PROJECT_STREAMZ_H
class StreamZ{
private:
    UserManager userManager;
    ViewerManager viewerManager;
    StreamManager streamManager;
    StreamerManager streamerManager;
    AdminManager adminManager;
    LeaderboardManager leaderboardManager;

public:
    StreamZ();
    /*
    void filterAge(unsigned int minAge);
    void filterLanguage(std::string streamLang);
    void sortByViews(int order);
    void showActiveStreams();*/
};

#endif //PROJECT_STREAMZ_H
