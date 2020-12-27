//
// Created by biromiro on 01/11/20.
//

#include <gtest/gtest.h>
#include <model/stream/stream.h>
#include <model/stream/privateStream/privateStream.h>
#include <model/stream/publicStream/publicStream.h>
#include <model/stream/finishedStream/finishedStream.h>
#include <model/user/streamer/streamer.h>
#include <model/user/viewer/viewer_manager.h>
#include <model/stream/streamManager.h>
#include <model/user/streamer/streamer_manager.h>
#include <exception/userAlreadyExists/userAlreadyExists.h>
#include <exception/userNotFound/userNotFound.h>

TEST(streamer_manager, build){
    std::shared_ptr<UserManager> um1 =  std::make_shared<UserManager>();
    std::shared_ptr<ViewerManager> vm1 = std::make_shared<ViewerManager>(um1);
    std::shared_ptr<StreamManager> sm1 = std::make_shared<StreamManager>(vm1, std::make_shared<StreamerManager>());
    std::shared_ptr<StreamerManager>srm1 = std::make_shared<StreamerManager>(sm1, vm1, um1);
    Date birthdate(2001,5,16);
    EXPECT_EQ(srm1->getStreamers().size(), 0);
    srm1->build(birthdate,"rhaast gaming","rhaast gaming","obey!");
    EXPECT_EQ(srm1->getStreamers().size(), 1);
    EXPECT_THROW(srm1->build(birthdate,"kayn gaming","rhaast gaming","bruh"),NicknameAlreadyAdded);
}

TEST(streamer_manager, add_remove){
    std::shared_ptr<UserManager> um1 =  std::make_shared<UserManager>();
    std::shared_ptr<ViewerManager> vm1 = std::make_shared<ViewerManager>(um1);
    std::shared_ptr<StreamManager> sm1 = std::make_shared<StreamManager>(vm1, std::make_shared<StreamerManager>());
    std::shared_ptr<StreamerManager>srm1 = std::make_shared<StreamerManager>(sm1, vm1, um1);
    Date birthdate(2001,5,16);
    auto streamer = std::make_shared<Streamer>(birthdate,"darius gaming","bruh gaming","123456");
    auto streamer2 = srm1->build(birthdate,"swaaaain","whitout love","swaaaain");
    EXPECT_EQ(srm1->add(streamer),true);
    EXPECT_THROW(srm1->add(streamer),UserAlreadyExists);
    EXPECT_EQ(srm1->remove(streamer2),true);
    EXPECT_THROW(srm1->remove(streamer2),UserNotFound);
}

TEST(streamer_manager,has_get){
    std::shared_ptr<UserManager> um1 =  std::make_shared<UserManager>();
    std::shared_ptr<ViewerManager> vm1 = std::make_shared<ViewerManager>(um1);
    std::shared_ptr<StreamManager> sm1 = std::make_shared<StreamManager>(vm1, std::make_shared<StreamerManager>());
    std::shared_ptr<StreamerManager>srm1 = std::make_shared<StreamerManager>(sm1, vm1, um1);
    Date birthdate(2001,5,16);
    EXPECT_EQ(srm1->has("Nautilus gaming"),false);
    auto streamer1 = srm1->build(birthdate,"Bruj45","Nautilus gaming","op champ pls nerf");
    EXPECT_EQ(srm1->has("Nautilus gaming"),true);
    EXPECT_EQ(srm1->has(streamer1),true);
    EXPECT_EQ(srm1->get("Nautilus gaming"),streamer1);
}

TEST(streamer_manager,deactivate_activate){
    std::shared_ptr<UserManager> um1 =  std::make_shared<UserManager>();
    std::shared_ptr<ViewerManager> vm1 = std::make_shared<ViewerManager>(um1);
    std::shared_ptr<StreamManager> sm1 = std::make_shared<StreamManager>(vm1, std::make_shared<StreamerManager>());
    std::shared_ptr<StreamerManager>srm1 = std::make_shared<StreamerManager>(sm1, vm1, um1);
    Date birthdate(2001,5,16);
    auto s1 = std::make_shared<Streamer>(birthdate,"darius gaming","bruh gaming","123456");
    EXPECT_THROW(srm1->deactivateStreamer(s1),UserNotFound);
    auto s2 = srm1->build(birthdate,"Teemo jungle","gg ez","123456");
    EXPECT_EQ(s2->isDeactivated(),false);
    EXPECT_EQ(srm1->deactivateStreamer(s2),true);
    EXPECT_EQ(s2->isDeactivated(),true);
    EXPECT_THROW(srm1->reactivateStreamer(s1),UserNotFound);
    EXPECT_EQ(srm1->reactivateStreamer(s2),true);
}