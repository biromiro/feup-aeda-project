//
// Created by biromiro on 01/11/20.
//


#include <gtest/gtest.h>
#include <user/user_manager.h>
#include <user/viewer/viewer_manager.h>
#include <user/streamer/streamer_manager.h>
#include <stream/streamManager.h>
#include <utils/leaderboard/leaderboard_manager.h>


using testing::Eq;


TEST(leaderboard_manager, filters){
    UserManager userManager;
    ViewerManager viewerManager(&userManager);
    StreamManager streamManager(&viewerManager);
    StreamerManager streamerManager(&streamManager,&viewerManager,&userManager);
    LeaderboardManager leaderboardManager(&viewerManager,&streamerManager,&streamManager);

    Date birthDate("2001/10/20");
    viewerManager.build(birthDate,"André Moreira","Dustini");
    viewerManager.build(birthDate,"André Pereira","dustibo");
    streamerManager.build(birthDate, "Nuno Costa", "biromiro");
    auto s = streamerManager.build(birthDate, "oscar ESteves", "biroadsadiro");
    streamManager.build("jebcnhuwbwiu",PT_PT,18,PUBLIC,s);

    auto streamers = leaderboardManager.sortStreamersByNickname();
    std::cout << streamers;
}
