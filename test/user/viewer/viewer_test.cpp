//
// Created by biromiro on 18/10/20.
//


#include <gtest/gtest.h>
#include <stream/publicStream/publicStream.h>
#include <stream/privateStream/privateStream.h>
#include <user/viewer/viewer.h>
#include <user/streamer/streamer.h>

using testing::Eq;


TEST(viewer, constructor){
    Date birthDate(2000,11,18);
    Viewer viewer1(birthDate, "Palpa", "Palps");
    EXPECT_EQ(viewer1.getUserType(), UserTypes::VIEWER);
}

TEST(viewer, constructor_test_invalid_age){
    Date birthDate(2010,11,18);
    EXPECT_THROW(Viewer viewer(birthDate,"Palpa","Palps"), std::invalid_argument);
    try{
        Viewer viewer(birthDate,"Palpa","Palps");
    }
    catch (const std::invalid_argument &ia) {
        std::string message = ia.what();
        EXPECT_EQ(message, "Minimum Age Not Met");
    }
}

TEST(viewer, joinStream){
    Date birthDate1(2000,11,18), birthDate2(2005,11,18);
    auto streamer = std::make_shared<Streamer>(birthDate1,"adasda adasda","ededfeqw");
    auto stream = std::make_shared<PublicStream>("New Stream!",PT_PT,18,GAMING,streamer);
    auto viewer = std::make_shared<Viewer>(birthDate1,"André Moreira","Dustini");
    auto viewer2 = std::make_shared<Viewer>(birthDate2,"Epic Man","epic");
    EXPECT_EQ(viewer->joinStream(std::dynamic_pointer_cast<Stream>(stream)),true);
    EXPECT_EQ(viewer2->joinStream(std::dynamic_pointer_cast<Stream>(stream)),false);
}

TEST(viewer, iswatchingstream_leave){
    Date birthDate1(2000,11,18), birthDate2(2005,11,18);
    auto streamer = std::make_shared<Streamer>(birthDate1,"adasda adasda","ededfeqw");
    auto stream = std::make_shared<PublicStream>("New Stream!",PT_PT,18, GAMING, streamer);
    auto viewer = std::make_shared<Viewer>(birthDate1,"André Moreira","Dustini");
    auto viewer2 = std::make_shared<Viewer>(birthDate2,"Epic Man","epic");
    EXPECT_EQ(viewer->isWatchingStream(),false);
    EXPECT_EQ(viewer->joinStream(std::dynamic_pointer_cast<Stream>(stream)),true);
    EXPECT_EQ(viewer->isWatchingStream(),true);
    EXPECT_EQ(viewer2->isWatchingStream(),false);
    EXPECT_EQ(viewer2->joinStream(std::dynamic_pointer_cast<Stream>(stream)),false);
    EXPECT_EQ(viewer2->isWatchingStream(),false);
    viewer->leaveCurrentStream();
    EXPECT_EQ(viewer->isWatchingStream(),false);
}

TEST(viewer, giveFeedback){
    Date birthDate1(2000,11,18), birthDate2(1998,11,18);
    auto streamer = std::make_shared<Streamer>(birthDate1,"adasda adasda","ededfeqw");
    auto stream = std::make_shared<PublicStream>("New Stream!",PT_PT,18, GAMING,streamer);
    auto streamer2 = std::make_shared<Streamer>(birthDate1,"dsadsdasda","asdad");
    auto stream2 = std::make_shared<PrivateStream>("New!",PT_BR,18, COOKING, streamer2);
    auto viewer = std::make_shared<Viewer>(birthDate1,"André Moreira","Dustini");
    auto viewer2 = std::make_shared<Viewer>(birthDate2,"Epic Man","epic");
    stream2->addToWhitelist(viewer2);
    stream2->setMaxNumViewers(5);
    EXPECT_EQ(viewer->giveFeedbackToStream(LIKE),false);
    viewer->joinStream(std::dynamic_pointer_cast<Stream>(stream));
    EXPECT_EQ(viewer->giveFeedbackToStream(LIKE),true);
    EXPECT_EQ(viewer->giveFeedbackToStream("kekw"),false);
    EXPECT_EQ(viewer2->joinStream(std::dynamic_pointer_cast<Stream>(stream2)),true);
    EXPECT_EQ(viewer2->giveFeedbackToStream(LIKE),true);
    EXPECT_EQ(viewer2->giveFeedbackToStream("kekw"),true);
}

TEST(viewer, follow_unfollow){
    Date birthDate1(2000,11,18), birthDate2(1998,11,18);
    auto viewer = std::make_shared<Viewer>(birthDate1,"André Moreira","Dustini");
    auto streamer = std::make_shared<Streamer>(birthDate2,"João Baltazar", "rand0mizer");
    auto streamer2 = std::make_shared<Streamer>(birthDate2,"Óscar Esteves", "vespasiano");
    auto streamer3 = std::make_shared<Streamer>(birthDate2,"Joel Fernandes", "jelgamerplayer");
    EXPECT_EQ(viewer->getFollowingStreamers().size(),0);
    EXPECT_EQ(viewer->followStreamer(streamer),true);
    EXPECT_EQ(viewer->followStreamer(streamer),false);
    EXPECT_EQ(viewer->getFollowingStreamers().size(),1);
    EXPECT_EQ(viewer->followStreamer(streamer2),true);
    EXPECT_EQ(viewer->getFollowingStreamers().size(),2);
    EXPECT_EQ(viewer->unfollowStreamer(streamer3),false);
    EXPECT_EQ(viewer->unfollowStreamer(streamer2),true);
    EXPECT_EQ(viewer->getFollowingStreamers().size(),1);
}