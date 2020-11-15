//
// Created by Danny on 08/11/2020.
//

#include <gtest/gtest.h>
#include <model/stream/privateStream/privateStream.h>
#include <model/user/streamer/streamer.h>

using testing::Eq;

TEST(privateStream, constructor){
    Date birthDate(1985,05,26);
    Streamer streamer1(birthDate, "Jogador Silva", "xXjogadorXx", "najkshndisakda");
    PrivateStream stream_no_args;
    PrivateStream stream1("Epic LoL Stream", EN, 13, GAMING, std::make_shared<Streamer>(streamer1));
    EXPECT_EQ(stream_no_args.getStreamType(), StreamType::PRIVATE);
    EXPECT_EQ(stream1.getStreamType(), StreamType::PRIVATE);
}

TEST(privateStream, getWhitelist){
    Date birthDate(1985,05,26);
    Streamer streamer1(birthDate, "Jogador Silva", "xXjogadorXx", "kahdjknads");
    Streamer streamer2(birthDate, "Funny Numbers Haha", "69420", "knadkonadsa");
    Viewer viewer1(birthDate, "Simp", "PokimaneLover", "knaskoja");
    Viewer viewer2(birthDate, "Simp2", "PokimaneLover2", "knodaijbnads");
    PrivateStream stream1("Epic LoL Stream", EN, 13, GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Cringe LoL Stream", CZ, 21, GAMING, std::make_shared<Streamer>(streamer2));
    stream1.addToWhitelist(std::make_shared<Viewer>(viewer1));
    stream1.addToWhitelist(std::make_shared<Viewer>(viewer2));
    stream2.addToWhitelist(std::make_shared<Viewer>(viewer1));
    std::vector<std::string> expected_wl1 = {"PokimaneLover", "PokimaneLover2"};
    std::vector<std::string> expected_wl2 = {"PokimaneLover"};
    EXPECT_EQ(stream1.getWhitelist(), expected_wl1);
    EXPECT_EQ(stream2.getWhitelist(), expected_wl2);
    stream2.removeFromWhitelist(std::make_shared<Viewer>(viewer1));
    std::vector<std::string> expected_wl3;
    EXPECT_EQ(stream2.getWhitelist(), expected_wl3);
}

TEST(privateStream, getMaxNumViewers){
    Date birthDate(1985,05,26);
    Streamer streamer1(birthDate, "Jogador Silva", "xXjogadorXx", "knasijkodhnas");
    PrivateStream stream_no_args;
    PrivateStream stream1("Epic LoL Stream", EN, 13, GAMING, std::make_shared<Streamer>(streamer1));
    stream_no_args.setMaxNumViewers(1000);
    stream1.setMaxNumViewers(275);
    EXPECT_EQ(stream_no_args.getMaxNumViewers(), 1000);
    EXPECT_EQ(stream1.getMaxNumViewers(), 275);
}

TEST(privateStream, getComments){
    Date birthDate(1985,05,26);
    Streamer streamer1(birthDate, "Jogador Silva", "xXjogadorXx", "kajshnasda");
    PrivateStream stream_no_args;
    PrivateStream stream1("Epic LoL Stream", EN, 13, GAMING, std::make_shared<Streamer>(streamer1));
    stream_no_args.addComment("WOW! This stream is so epic!!!");
    stream_no_args.addComment("How can I donate?");
    std::vector<std::string> expected_cm1 = {"WOW! This stream is so epic!!!", "How can I donate?"};
    std::vector<std::string> expected_cm2;
    EXPECT_EQ(stream_no_args.getComments(), expected_cm1);
    EXPECT_EQ(stream1.getComments(), expected_cm2);
}

TEST(privateStream, canJoin){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "jknadjkhnasida");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "knajkodhnaisda");
    PrivateStream stream1("Epic LoL Stream", EN, 13, GAMING, std::make_shared<Streamer>(streamer1));
    Viewer viewer1(birthDate2,"Visualizador Não Pog","Pogn't", "inasjkbndaisda");
    Viewer viewer2(birthDate1,"Visualizador Pog","Pog", "knadiuohsndas");
    std::shared_ptr<PrivateStream> stream1_ptr = std::make_shared<PrivateStream>(stream1);
    stream1.setMaxNumViewers(275);
    std::shared_ptr<Viewer> viewer1_ptr = std::make_shared<Viewer>(viewer1);
    std::shared_ptr<Viewer> viewer2_ptr = std::make_shared<Viewer>(viewer2);
    stream1.addToWhitelist(viewer1_ptr);
    stream1.addToWhitelist(viewer2_ptr);
    EXPECT_EQ(viewer1_ptr->joinStream(stream1_ptr), true);
    EXPECT_EQ(viewer2_ptr->joinStream(stream1_ptr), true);
    EXPECT_EQ(stream1.getNumOfViewers(), 2);
}