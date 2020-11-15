//
// Created by biromiro on 01/11/20.
//

#include <gtest/gtest.h>
#include <model/user/streamer/streamer.h>


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
        std::string message = ia.getMessage();
        EXPECT_EQ(message,"You have to be at least 15 years old!");
    }
}

TEST(streamer, isStreaming_setStream_removeStream){
    Date birthdate(2001,5,16);
}