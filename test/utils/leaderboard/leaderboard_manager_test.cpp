//
// Created by biromiro on 02/11/20.
//

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


TEST(leaderboard_manager, sorts){
    std::shared_ptr<UserManager> userManager =  std::make_shared<UserManager>();
    std::shared_ptr<ViewerManager> viewerManager = std::make_shared<ViewerManager>(userManager);
    std::shared_ptr<StreamManager> streamManager = std::make_shared<StreamManager>(viewerManager);
    std::shared_ptr<StreamerManager> streamerManager = std::make_shared<StreamerManager>(streamManager,viewerManager,userManager);
    std::shared_ptr<LeaderboardManager> leaderboardManager = std::make_shared<LeaderboardManager>(viewerManager,streamerManager,streamManager,userManager);

    Date birthDate("2001/10/20");
    viewerManager->build(birthDate,"André Moreira","Dustini");
    viewerManager->build(birthDate,"André Pereira","dustibo");
    streamerManager->build(birthDate, "Nuno Costa", "biromiro");
    auto s = streamerManager->build(birthDate, "oscar ESteves", "biroadsadiro");
    streamManager->build("jebcnhuwbwiu",PT_PT,18,PUBLIC,COOKING,s);

    auto streamers = leaderboardManager->sortStreamers();
    std::cout << streamers;
}

TEST(leaderboard_manager, filters){
    std::shared_ptr<UserManager> userManager =  std::make_shared<UserManager>();
    std::shared_ptr<ViewerManager> viewerManager = std::make_shared<ViewerManager>(userManager);
    std::shared_ptr<StreamManager> streamManager = std::make_shared<StreamManager>(viewerManager);
    std::shared_ptr<StreamerManager> streamerManager = std::make_shared<StreamerManager>(streamManager,viewerManager,userManager);
    std::shared_ptr<LeaderboardManager> leaderboardManager = std::make_shared<LeaderboardManager>(viewerManager,streamerManager,streamManager,userManager);

    Date birthDate("2001/10/20");
    viewerManager->build(birthDate,"André Moreira","Dustini");
    viewerManager->build(birthDate,"André Pereira","dustibo");
    auto s1 = streamerManager->build(birthDate, "Nuno Costa", "biromiro");
    auto s2 = streamerManager->build(birthDate, "oscar ESteves", "biroadsadiro");
    auto s3 = streamerManager->build(birthDate, "Paulo Costa", "vespa");
    auto s4 = streamerManager->build(birthDate, "Carlos ESteves", "dustibo");
    streamManager->build("jebcnhuwbwiu",PT_PT,18,PUBLIC, COOKING, s1);
    streamManager->build("esfw",AZ,10,PUBLIC, COOKING, s2);
    streamManager->build("asd",EN,15,PRIVATE, GAMING, s3);

    auto streamers = leaderboardManager->sortStreamers();
    std::cout << streamers;

    auto viewers = leaderboardManager->sortViewers();
    std::cout << viewers;

    auto users = leaderboardManager->sortUsers();
    std::cout << users;

    auto streams = leaderboardManager->sortStreams();
    std::cout << streams;
}
