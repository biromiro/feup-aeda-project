//
// Created by Danny on 03/11/2020.
//

#include <gtest/gtest.h>
#include <model/stream/stream.h>
#include <model/stream/privateStream/privateStream.h>
#include <model/stream/publicStream/publicStream.h>
#include <model/stream/finishedStream/finishedStream.h>
#include <model/user/streamer/streamer.h>


using testing::Eq;

TEST(stream, getNumOfViewers){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "olaamego");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "muitofixemeu");
    PublicStream stream1("Epic LoL Stream", EN, 13, GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", EN, 18, GAMING, std::make_shared<Streamer>(streamer2));
    FinishedStream stream3 ("?????", PT_PT, 10, COOKING, std::make_shared<Streamer>(streamer2), 50);
    EXPECT_EQ(stream1.getNumOfViewers(), 0);
    EXPECT_EQ(stream3.getNumOfViews(), 50);
}

TEST(stream, getMinAge){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "sentiatensao");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "muitofixemeu");
    PublicStream stream1("Epic LoL Stream", EN, 13, GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", EN, 18, GAMING, std::make_shared<Streamer>(streamer2));
    FinishedStream stream3 ("?????", PT_PT, 10, COOKING, std::make_shared<Streamer>(streamer2), 50);
    EXPECT_EQ(stream1.getMinAge(), 13);
    EXPECT_EQ(stream2.getMinAge(), 18);
    EXPECT_EQ(stream3.getMinAge(), 10);
}

TEST(stream, getTitle){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "muitofixemeu");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "homembase");
    PublicStream stream1("Epic LoL Stream", EN, 13, GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", EN, 18, GAMING, std::make_shared<Streamer>(streamer2));
    FinishedStream stream3 ("?????", PT_PT, 10, COOKING, std::make_shared<Streamer>(streamer2), 50);
    EXPECT_EQ(stream1.getTitle(), "Epic LoL Stream");
    EXPECT_EQ(stream2.getTitle(), "Based Games");
    EXPECT_EQ(stream3.getTitle(), "?????");
}

TEST(stream, getLanguage){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "eusouautofeito");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "olaoscra");
    PublicStream stream1("Epic LoL Stream", EN, 13, GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", RU, 18, GAMING, std::make_shared<Streamer>(streamer2));
    FinishedStream stream3 ("?????", PT_PT, 10, COOKING, std::make_shared<Streamer>(streamer2), 50);
    EXPECT_EQ(stream1.getLanguage(), EN);
    EXPECT_EQ(stream2.getLanguage(), RU);
    EXPECT_EQ(stream3.getLanguage(), PT_PT);
}

TEST(stream, getStreamDate){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "olaoscra");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "euvoulevarmute");
    PublicStream stream1("Epic LoL Stream", EN, 13, GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", EN, 18, GAMING, std::make_shared<Streamer>(streamer2));
    FinishedStream stream3 ("?????", PT_PT, 10, COOKING, std::make_shared<Streamer>(streamer2), 50);
    EXPECT_EQ(stream1.getMinAge(), 13);
    EXPECT_EQ(stream2.getMinAge(), 18);
    EXPECT_EQ(stream3.getMinAge(), 10);
}



TEST(stream, getStreamer){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "cheirameabase");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "muitofixemeu");
    std::shared_ptr<Streamer> streamer1_ptr = std::make_shared<Streamer>(streamer1);
    std::shared_ptr<Streamer> streamer2_ptr = std::make_shared<Streamer>(streamer2);
    PublicStream stream1("Epic LoL Stream", EN, 13, GAMING, streamer1_ptr);
    PrivateStream stream2("Based Games", EN, 18, GAMING, streamer2_ptr);
    FinishedStream stream3 ("?????", PT_PT, 10, COOKING, streamer2_ptr, 50);
    EXPECT_EQ(stream1.getStreamer(), streamer1_ptr);
    EXPECT_EQ(stream2.getStreamer(), streamer2_ptr);
    EXPECT_EQ(stream3.getStreamer(), streamer2_ptr);
}

TEST(stream, getGenre){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "sintoatensao");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "algosepassa");
    PublicStream stream1("Epic LoL Stream", EN, 13, GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", EN, 18, TALKSHOW, std::make_shared<Streamer>(streamer2));
    FinishedStream stream3 ("?????", PT_PT, 10, COOKING, std::make_shared<Streamer>(streamer2), 50);
    PrivateStream stream4("Top Hits 1857", ES, 3, MUSIC, std::make_shared<Streamer>(streamer1));
    EXPECT_EQ(stream1.getGenre(), GAMING);
    EXPECT_EQ(stream2.getGenre(), TALKSHOW);
    EXPECT_EQ(stream3.getGenre(), COOKING);
    EXPECT_EQ(stream4.getGenre(), MUSIC);
}

TEST(stream, addFeedback){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "123ola123");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "baseado890");
    PublicStream stream1("Epic LoL Stream", EN, 13, GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", EN, 18, GAMING, std::make_shared<Streamer>(streamer2));
    FinishedStream stream3 ("?????", PT_PT, 10, COOKING, std::make_shared<Streamer>(streamer2), 50);
    stream1.addFeedback(LIKE);
    stream1.addFeedback(LIKE);
    stream1.addFeedback(LIKE);
    stream1.addFeedback(DISLIKE);
    stream2.addFeedback(DISLIKE);
    stream2.addFeedback(DISLIKE);
    stream3.addFeedback(LIKE);
    stream3.addFeedback(DISLIKE);
    stream3.addFeedback(INVALID_VOTE);
    EXPECT_EQ(stream1.getVotes().first, 3);
    EXPECT_EQ(stream1.getVotes().second, 1);
    EXPECT_EQ(stream2.getVotes().first, 0);
    EXPECT_EQ(stream2.getVotes().second, 2);
    EXPECT_EQ(stream3.getVotes().first, 1);
    EXPECT_EQ(stream3.getVotes().second, 1);
}
