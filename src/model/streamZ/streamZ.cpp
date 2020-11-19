//
// Created by emanu on 21-Oct-20.
//

#include "streamZ.h"

StreamZ::StreamZ() :
userManager(std::make_shared<UserManager>()),
viewerManager(std::make_shared<ViewerManager>(userManager)),
streamManager(std::make_shared<StreamManager>(viewerManager,std::make_shared<StreamerManager>())),
streamerManager(std::make_shared<StreamerManager>(streamManager, viewerManager, userManager)),
adminManager( std::make_shared<AdminManager>(userManager)),
leaderboardManager(std::make_shared<LeaderboardManager>(viewerManager,streamerManager,streamManager,userManager)){
    streamManager->setStreamerManager(streamerManager);
}


std::shared_ptr<UserManager> StreamZ::getUserManager() {
    return userManager;
}

std::shared_ptr<ViewerManager> StreamZ::getViewerManager() {
    return viewerManager;
}

std::shared_ptr<StreamManager> StreamZ::getStreamManager() {
    return streamManager;
}

std::shared_ptr<StreamerManager> StreamZ::getStreamerManager() {
    return streamerManager;
}

std::shared_ptr<LeaderboardManager> StreamZ::getLeaderboardManager() {
    return leaderboardManager;
}

void StreamZ::initialize() {
    streamerManager->readData();
    streamManager->readData();
    viewerManager->readData(streamManager);
    adminManager->readData();
}

void StreamZ::finish() {
    streamerManager->writeData();
    streamManager->writeData();
    viewerManager->writeData();
    adminManager->writeData();
}
