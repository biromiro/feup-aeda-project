//
// Created by Danny on 08/11/2020.
//

#include <gtest/gtest.h>
#include <model/stream/privateStream/privateStream.h>
#include <model/stream/publicStream/publicStream.h>
#include <model/stream/finishedStream/finishedStream.h>
#include <model/user/streamer/streamer.h>
#include <model/user/user_manager.h>
#include <model/user/viewer/viewer_manager.h>
#include <model/stream/streamManager.h>
#include <model/user/streamer/streamer_manager.h>

using testing::Eq;

/* Só funciona se for corrido isoladamente!
TEST(finishedStream, getters) {
    std::shared_ptr<UserManager> um1 =  std::make_shared<UserManager>();
    std::shared_ptr<ViewerManager> vm1 = std::make_shared<ViewerManager>(um1);
    std::shared_ptr<StreamManager> sm1 = std::make_shared<StreamManager>(vm1, std::make_shared<StreamerManager>());
    std::shared_ptr<StreamerManager> stm1 = std::make_shared<StreamerManager>(sm1,vm1,um1);
    sm1->setStreamerManager(stm1);
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "olaamego");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "muitofixemeu");
    auto stream1 = std::dynamic_pointer_cast<PublicStream>(sm1->build("Epic LoL Stream", StreamLanguage::EN, 13, StreamType::PUBLIC, StreamGenre::GAMING, std::make_shared<Streamer>(streamer1)));
    auto finished1 = sm1->finish(stream1);
    EXPECT_EQ(finished1->getStreamType(), StreamType::FINISHED);
    EXPECT_EQ(finished1->getNumOfViews(), 0);
    EXPECT_EQ(finished1->getID(), 1);
} */
