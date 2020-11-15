//
// Created by Danny on 08/11/2020.
//

#include <gtest/gtest.h>
#include <stream/publicStream/publicStream.h>
#include <user/streamer/streamer.h>

using testing::Eq;

TEST(publicStream, constructor){
    Date birthDate(1985,05,26);
    Streamer streamer1(birthDate, "Jogador Silva", "xXjogadorXx");
    PublicStream stream_no_args;
    PublicStream stream1("Epic LoL Stream", EN, 13, GAMING, std::make_shared<Streamer>(streamer1));
    EXPECT_EQ(stream_no_args.getStreamType(), StreamType::PUBLIC);
    EXPECT_EQ(stream1.getStreamType(), StreamType::PUBLIC);
}

