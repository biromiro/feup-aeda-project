//
// Created by biromiro on 01/11/20.
//

#include <gtest/gtest.h>
#include "user/streamer/streamer.h"


TEST(streamer, constructor){
    Date birthDate(2001,5,16);
    Streamer streamer(birthDate,"Cao manteiga","buttah dog");
    EXPECT_EQ(streamer.getUserType(),UserTypes::STREAMER);
}

TEST(streamer, constructor_invalid_age){
    Date birthDate(2011,5,16);
    EXPECT_THROW(Streamer streamer(birthDate,"Cao manteiga","dog"),std::invalid_argument);
    try{
        Streamer streamer(birthDate,"Cao manteiga","dog");
    }
    catch(const std::invalid_argument &ia){
        std::string message = ia.what();
        EXPECT_EQ(message,"Minimum Age Not Met");
    }
}

TEST(streamer, isStreaming_setStream_removeStream){
    Date birthdate(2001,5,16);
}