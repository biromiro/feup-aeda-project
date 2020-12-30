//
// Created by biromiro on 13/10/20.
//

#ifndef PROJECT_STREAMZ_H
#define PROJECT_STREAMZ_H

#include "../user/viewer/viewer_manager.h"
#include "../user/streamer/streamer_manager.h"
#include "../user/admin/admin_manager.h"
#include "../user/user_manager.h"
#include "../stream/streamManager.h"
#include "../../utils/leaderboard/leaderboard_manager.h"
#include <vector>
#include <string>
#include <fstream>

/**
 * @file streamZ.cpp
 *
 * @brief Class representing the streamZ class
 *
 * @ingroup streamZ
 */

/**
 * Implementation of the StreamZ class
 *
 * Represents the platform, encapsulating all of its components
 */
class StreamZ{
private:
    std::shared_ptr<UserManager> userManager;
    std::shared_ptr<ViewerManager> viewerManager;
    std::shared_ptr<StreamManager> streamManager;
    std::shared_ptr<StreamerManager> streamerManager;
    std::shared_ptr<AdminManager> adminManager;
    std::shared_ptr<LeaderboardManager> leaderboardManager;

public:
    /**
     * Constructor of the streamZ class
     *
     * Sets empty managers
     * */
    StreamZ();

    /**
     * Initializes the objects saved in files by reading them using the managers
     * */
    void initialize();

    /**
     * Updates and saves objects created in the respective files
     * */
    void finish();

    /**
     * Method to obtain the userManager
     * @return pointer to current userManager
     * */
    std::shared_ptr<UserManager> getUserManager();

    /**
    * Method to obtain the viewerManager
    * @return pointer to current viewerManager
     * */
    std::shared_ptr<ViewerManager> getViewerManager();

    /**
    * Method to obtain the streamManager
    * @return pointer to current streamManager
     * */
    std::shared_ptr<StreamManager> getStreamManager();

    /**
    * Method to obtain the streamerManager
    * @return pointer to current streamerManager
     * */
    std::shared_ptr<StreamerManager> getStreamerManager();

    /**
    * Method to obtain the leaderboardManager
    * @return pointer to current leaderboardManager
     * */
    std::shared_ptr<LeaderboardManager> getLeaderboardManager();

    /**
    * Method to obtain the adminManager
    * @return pointer to current adminManager
     * */
    std::shared_ptr<AdminManager> getAdminManager();
};

#endif //PROJECT_STREAMZ_H
