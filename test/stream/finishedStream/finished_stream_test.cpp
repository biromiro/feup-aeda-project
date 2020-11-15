//
// Created by Danny on 08/11/2020.
//

#include <gtest/gtest.h>
#include <stream/privateStream/privateStream.h>
#include <stream/publicStream/publicStream.h>
#include <stream/finishedStream/finishedStream.h>
#include <user/streamer/streamer.h>

using testing::Eq;

TEST(finishedStream, getters) {
    Date birthDate(1985,05,26);
    Streamer streamer1(birthDate, "Jogador Silva", "xXjogadorXx");
    FinishedStream stream1("Epic LoL Stream", EN, 13, GAMING, std::make_shared<Streamer>(streamer1), 500);
    std::shared_ptr<FinishedStream> stream1_ptr = std::make_shared<FinishedStream>(stream1);
    EXPECT_EQ(stream1_ptr->getStreamType(), FINISHED);
    EXPECT_EQ(stream1_ptr->getNumOfViews(), 500);
}
