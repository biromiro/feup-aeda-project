//
// Created by Danny on 08/11/2020.
//

#include <gtest/gtest.h>
#include <model/stream/privateStream/privateStream.h>
#include <model/user/streamer/streamer.h>
#include <model/user/user_manager.h>
#include <model/user/viewer/viewer_manager.h>
#include <model/stream/streamManager.h>
#include <model/user/streamer/streamer_manager.h>
#include <exception/nicknameNotFound.h>
#include <exception/nicknameAlreadyAdded.h>

using testing::Eq;

TEST(privateStream, constructor){
    Date birthDate(1985,05,26);
    Streamer streamer1(birthDate, "Jogador Silva", "xXjogadorXx", "najkshndisakda");
    PrivateStream stream_no_args;
    PrivateStream stream1("Epic LoL Stream", StreamLanguage::EN, 13, StreamGenre::GAMING, std::make_shared<Streamer>(streamer1));
    EXPECT_EQ(stream_no_args.getStreamType(), StreamType::PRIVATE);
    EXPECT_EQ(stream1.getStreamType(), StreamType::PRIVATE);
}

TEST(privateStream, getWhitelist){
    Date birthDate(1985,05,26);
    Streamer streamer1(birthDate, "Jogador Silva", "xXjogadorXx", "kahdjknads");
    Streamer streamer2(birthDate, "Funny Numbers Haha", "69420", "knadkonadsa");
    Viewer viewer1(birthDate, "Simp", "PokimaneLover", "knaskoja");
    Viewer viewer2(birthDate, "Simp2", "PokimaneLover2", "knodaijbnads");
    PrivateStream stream1("Epic LoL Stream", StreamLanguage::EN, 13, StreamGenre::GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Cringe LoL Stream", StreamLanguage::CZ, 21, StreamGenre::GAMING, std::make_shared<Streamer>(streamer2));
    stream1.addToWhitelist(std::make_shared<Viewer>(viewer1));
    EXPECT_THROW(stream1.addToWhitelist(std::make_shared<Viewer>(viewer1)), NicknameAlreadyAdded);
    try {
        stream1.addToWhitelist(std::make_shared<Viewer>(viewer1));
    }
    catch (NicknameAlreadyAdded &naa) {
        EXPECT_EQ(naa.getMessage(), "Viewer you're trying to add is already in the whitelist!");
    }
    stream1.addToWhitelist(std::make_shared<Viewer>(viewer2));
    stream2.addToWhitelist(std::make_shared<Viewer>(viewer1));
    std::vector<std::string> expected_wl1 = {"PokimaneLover", "PokimaneLover2"};
    std::vector<std::string> expected_wl2 = {"PokimaneLover"};
    EXPECT_EQ(stream1.getWhitelist(), expected_wl1);
    EXPECT_EQ(stream2.getWhitelist(), expected_wl2);
    stream2.removeFromWhitelist(std::make_shared<Viewer>(viewer1));
    std::vector<std::string> expected_wl3;
    EXPECT_EQ(stream2.getWhitelist(), expected_wl3);
    EXPECT_THROW(stream2.removeFromWhitelist(std::make_shared<Viewer>(viewer2)), NicknameNotFound);
    try {
        stream2.removeFromWhitelist(std::make_shared<Viewer>(viewer2));
    }
    catch (NicknameNotFound &nnf) {
        EXPECT_EQ(nnf.getMessage(), "Viewer is not in the whitelist!");
    }
}

TEST(privateStream, getMaxNumViewers){
    Date birthDate(1985,05,26);
    Streamer streamer1(birthDate, "Jogador Silva", "xXjogadorXx", "knasijkodhnas");
    PrivateStream stream_no_args;
    PrivateStream stream1("Epic LoL Stream", StreamLanguage::EN, 13, StreamGenre::GAMING, std::make_shared<Streamer>(streamer1));
    stream_no_args.setMaxNumViewers(1000);
    stream1.setMaxNumViewers(275);
    EXPECT_EQ(stream_no_args.getMaxNumViewers(), 1000);
    EXPECT_EQ(stream1.getMaxNumViewers(), 275);
}

TEST(privateStream, getComments){
    Date birthDate(1985,05,26);
    Streamer streamer1(birthDate, "Jogador Silva", "xXjogadorXx", "kajshnasda");
    PrivateStream stream_no_args;
    PrivateStream stream1("Epic LoL Stream", StreamLanguage::EN, 13, StreamGenre::GAMING, std::make_shared<Streamer>(streamer1));
    stream_no_args.addComment("WOW! This stream is so epic!!!");
    stream_no_args.addComment("How can I donate?");
    std::vector<std::string> expected_cm1 = {"WOW! This stream is so epic!!!", "How can I donate?"};
    std::vector<std::string> expected_cm2;
    EXPECT_EQ(stream_no_args.getComments(), expected_cm1);
    EXPECT_EQ(stream1.getComments(), expected_cm2);
}

TEST(privateStream, canJoin){
    std::shared_ptr<UserManager> um1 =  std::make_shared<UserManager>();
    std::shared_ptr<ViewerManager> vm1 = std::make_shared<ViewerManager>(um1);
    std::shared_ptr<StreamManager> sm1 = std::make_shared<StreamManager>(vm1, std::make_shared<StreamerManager>());
    std::shared_ptr<StreamerManager> stm1 = std::make_shared<StreamerManager>(sm1,vm1,um1);
    sm1->setStreamerManager(stm1);
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    auto streamer1 = stm1->build(birthDate1, "Oskar ÚltimoNome", "Autofeito", "jknadjkhnasida");
    auto streamer2 = stm1->build(birthDate2, "Homem Baseado", "Base", "knajkodhnaisda");
    auto stream1 = std::dynamic_pointer_cast<PrivateStream>(sm1->build("Epic LoL Stream", StreamLanguage::EN, 13, StreamType::PRIVATE, StreamGenre::GAMING, streamer1));
    auto viewer1 = vm1->build(birthDate2,"Visualizador Não Pog","Pogn't", "inasjkbndaisda");
    auto viewer2 = vm1->build(birthDate1,"Visualizador Pog","Pog", "knadiuohsndas");
    stream1->setMaxNumViewers(275);
    stream1->addToWhitelist(viewer1);
    stream1->addToWhitelist(viewer2);
    EXPECT_EQ(viewer1->joinStream(stream1), true);
    EXPECT_EQ(viewer2->joinStream(stream1), true);
    EXPECT_EQ(stream1->getNumOfViewers(), 2);
}