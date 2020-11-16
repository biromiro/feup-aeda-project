//
// Created by Danny on 08/11/2020.
//

#include <gtest/gtest.h>
#include <model/stream/privateStream/privateStream.h>
#include <model/stream/publicStream/publicStream.h>
#include <model/stream/finishedStream/finishedStream.h>
#include <model/user/streamer/streamer.h>

using testing::Eq;

TEST(finishedStream, getters) {
    Date birthDate(1985,05,26);
    Streamer streamer1(birthDate, "Jogador Silva", "xXjogadorXx", "ijnaiuadsas");
    FinishedStream stream1("Epic LoL Stream", StreamLanguage::EN, 13, StreamGenre::GAMING, std::make_shared<Streamer>(streamer1), 500);
    std::shared_ptr<FinishedStream> stream1_ptr = std::make_shared<FinishedStream>(stream1);
    EXPECT_EQ(stream1_ptr->getStreamType(), StreamType::FINISHED);
    EXPECT_EQ(stream1_ptr->getNumOfViews(), 500);
}
