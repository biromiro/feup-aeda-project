//
// Created by biromiro on 01/11/20.
//

#include <gtest/gtest.h>
#include <model/user/streamer/streamer.h>
#include <model/stream/publicStream/publicStream.h>


TEST(streamer, constructor){
    Date birthDate(2001,5,16);
    Streamer streamer(birthDate,"Cao manteiga","buttah dog","masya");
    EXPECT_EQ(streamer.getUserType(),UserTypes::STREAMER);
}

TEST(streamer, constructor_invalid_age){
    Date birthDate(2011,5,16);
    EXPECT_THROW(Streamer streamer(birthDate,"Cao manteiga","dog","tenso"),InvalidAge);
    try{
        Streamer streamer(birthDate,"Cao manteiga","dog", "aaaaaaaa");
    }
    catch(InvalidAge &ia){
        std::string message = ia.what();
        EXPECT_EQ(message,"You have to be at least 15 years old!");
    }
}

TEST(streamer, isStreaming_setStream_removeStream){
    Date birthDate1(2000,11,18);
    auto streamer = std::make_shared<Streamer>(birthDate1,"adasda adasda","ededfeqw", "sdasda");
    EXPECT_EQ(streamer->isStreaming(),false);
    auto stream = std::make_shared<PublicStream>("New Stream!",StreamLanguage::PT_PT,18,StreamGenre::GAMING,streamer);
    EXPECT_EQ(streamer->isStreaming(),false);
    streamer->setStream(stream);
    EXPECT_EQ(streamer->isStreaming(),true);
    streamer->removeStream();
    EXPECT_EQ(streamer->isStreaming(),false);
}
