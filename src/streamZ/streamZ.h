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
#include <fstream>
#include <filesystem>

#ifndef PROJECT_STREAMZ_H
#define PROJECT_STREAMZ_H
class StreamZ{
private:
    std::shared_ptr<UserManager> userManager;
    std::shared_ptr<ViewerManager> viewerManager;
    std::shared_ptr<StreamManager> streamManager;
    std::shared_ptr<StreamerManager> streamerManager;
    std::shared_ptr<AdminManager> adminManager;
    std::shared_ptr<LeaderboardManager> leaderboardManager;

public:
    StreamZ();

    void initialize();

    void finish();

    std::shared_ptr<UserManager> getUserManager();

    std::shared_ptr<ViewerManager> getViewerManager();

    std::shared_ptr<StreamManager> getStreamManager();

    std::shared_ptr<StreamerManager> getStreamerManager();

    std::shared_ptr<AdminManager> getAdminManager();

    std::shared_ptr<LeaderboardManager> getLeaderboardManager();
};

#endif //PROJECT_STREAMZ_H
