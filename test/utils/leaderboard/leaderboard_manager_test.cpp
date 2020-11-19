//
// Created by biromiro on 02/11/20.
//

//
// Created by biromiro on 01/11/20.
//


#include <gtest/gtest.h>
#include <model/user/user_manager.h>
#include <model/user/viewer/viewer_manager.h>
#include <model/user/streamer/streamer_manager.h>
#include <model/stream/streamManager.h>
#include <utils/leaderboard/leaderboard_manager.h>


using testing::Eq;


TEST(leaderboard_manager, sorts){
    std::shared_ptr<UserManager> userManager =  std::make_shared<UserManager>();
    std::shared_ptr<ViewerManager> viewerManager = std::make_shared<ViewerManager>(userManager);
    std::shared_ptr<StreamManager> streamManager = std::make_shared<StreamManager>(viewerManager,std::make_shared<StreamerManager>());
    std::shared_ptr<StreamerManager> streamerManager = std::make_shared<StreamerManager>(streamManager,viewerManager,userManager);
    std::shared_ptr<LeaderboardManager> leaderboardManager = std::make_shared<LeaderboardManager>(viewerManager,streamerManager,streamManager,userManager);
    streamManager->setStreamerManager(streamerManager);

    Date birthDate("2001/10/20");
    viewerManager->build(birthDate,"André Moreira","Dustini", "bitconnect!");
    viewerManager->build(birthDate,"André Pereira","dustibo", "hehasdksa");
    streamerManager->build(birthDate, "Nuno Costa", "biromiro", "dljekfchds");
    auto s = streamerManager->build(birthDate, "oscar ESteves", "biroadsadiro", "fhikcdhcguvds");
    streamManager->build("jebcnhuwbwiu",StreamLanguage::PT_PT,18,StreamType::PUBLIC,StreamGenre::COOKING,s);

    auto streamers = leaderboardManager->sortStreamers();
    std::cout << streamers;
}

TEST(leaderboard_manager, filters){
    std::shared_ptr<UserManager> userManager =  std::make_shared<UserManager>();
    std::shared_ptr<ViewerManager> viewerManager = std::make_shared<ViewerManager>(userManager);
    std::shared_ptr<StreamManager> streamManager = std::make_shared<StreamManager>(viewerManager,std::make_shared<StreamerManager>());
    std::shared_ptr<StreamerManager> streamerManager = std::make_shared<StreamerManager>(streamManager,viewerManager,userManager);
    std::shared_ptr<LeaderboardManager> leaderboardManager = std::make_shared<LeaderboardManager>(viewerManager,streamerManager,streamManager,userManager);
    streamManager->setStreamerManager(streamerManager);

    Date birthDate("2001/10/20"), birthDate2("2000/10/20");
    viewerManager->build(birthDate,"André Moreira","Dustini", "hehuebfghcudewc");
    viewerManager->build(birthDate,"André Pereira","dustibo", "autofeito");
    auto s1 = streamerManager->build(birthDate, "Nuno Costa", "biromiro", "hahduegvywbcs");
    auto s2 = streamerManager->build(birthDate2, "oscar ESteves", "biroadsadiro", "kekwjkaishduxyfasv");
    auto s3 = streamerManager->build(birthDate2, "Paulo Costa", "vespa", "kdfiocjikcs");
    auto s4 = streamerManager->build(birthDate, "Carlos ESteves", "epico", "jkcdhusgvbcs");
    streamManager->build("jebcnhuwbwiu",StreamLanguage::PT_PT,18,StreamType::PUBLIC, StreamGenre::COOKING, s1);
    streamManager->build("esfw",StreamLanguage::AZ,10,StreamType::PUBLIC, StreamGenre::COOKING, s2);
    streamManager->build("asd",StreamLanguage::EN,15,StreamType::PRIVATE, StreamGenre::GAMING, s3);

    auto streamers1 = leaderboardManager->sortStreamerBy(SortStreamer::NAME);
    auto streamers2 = leaderboardManager->sortStreamerBy(SortStreamer::NICKNAME);
    auto streamers3 = leaderboardManager->sortStreamerBy(SortStreamer::JOINDATE);
    auto streamers4 = leaderboardManager->sortStreamerBy(SortStreamer::BIRTHDATE);
    auto streamers5 = leaderboardManager->sortStreamerBy(SortStreamer::NUM_FOLLOWERS);
    auto streamers6 = leaderboardManager->sortStreamerBy(SortStreamer::STREAMING);
    auto streamers7 = leaderboardManager->sortStreamerBy(SortStreamer::VIEWCOUNT);

    std::cout << streamers1  << streamers2 << streamers3  << streamers4 << streamers5  << streamers6 << streamers7 << std::endl;

}

TEST(leaderboard_manager, getFollowingList){
    std::shared_ptr<UserManager> userManager =  std::make_shared<UserManager>();
    std::shared_ptr<ViewerManager> viewerManager = std::make_shared<ViewerManager>(userManager);
    std::shared_ptr<StreamManager> streamManager = std::make_shared<StreamManager>(viewerManager,std::make_shared<StreamerManager>());
    std::shared_ptr<StreamerManager> streamerManager = std::make_shared<StreamerManager>(streamManager,viewerManager,userManager);
    std::shared_ptr<LeaderboardManager> leaderboardManager = std::make_shared<LeaderboardManager>(viewerManager,streamerManager,streamManager,userManager);
    streamManager->setStreamerManager(streamerManager);

    Date birthDate("2001/10/20");
    auto v1 = viewerManager->build(birthDate,"André Moreira","Dustini", "hehuebfghcudewc");
    auto v2 = viewerManager->build(birthDate,"André Pereira","dustibo", "autofeito");
    auto s1 = streamerManager->build(birthDate, "Nuno Costa", "biromiro", "hahduegvywbcs");
    auto s2 = streamerManager->build(birthDate, "oscar ESteves", "biroadsadiro", "kekwjkaishduxyfasv");
    auto s3 = streamerManager->build(birthDate, "Paulo Costa", "vespa", "kdfiocjikcs");
    auto s4 = streamerManager->build(birthDate, "Carlos ESteves", "dustibo", "jkcdhusgvbcs");
    streamManager->build("jebcnhuwbwiu",StreamLanguage::PT_PT,18,StreamType::PUBLIC, StreamGenre::COOKING, s1);
    streamManager->build("esfw",StreamLanguage::AZ,10,StreamType::PUBLIC, StreamGenre::COOKING, s2);
    streamManager->build("asd",StreamLanguage::EN,15,StreamType::PRIVATE, StreamGenre::GAMING, s3);

    v1->followStreamer(s3);
    v1->followStreamer(s1);
    v2->followStreamer(s1);
    v2->followStreamer(s2);

    std::cout << leaderboardManager->getFollowingStreamersLeaderboard(v1) << std::endl;
    std::cout << leaderboardManager->getNotFollowingStreamersLeaderboard(v1) << std::endl;
    std::cout << leaderboardManager->getFollowingStreamersLeaderboard(v2) << std::endl;
    std::cout << leaderboardManager->getNotFollowingStreamersLeaderboard(v2) << std::endl;
}