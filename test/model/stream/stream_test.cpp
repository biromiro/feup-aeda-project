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
    PublicStream stream1("Epic LoL Stream", StreamLanguage::EN, 13, StreamGenre::GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", StreamLanguage::EN, 18, StreamGenre::GAMING, std::make_shared<Streamer>(streamer2));
    FinishedStream stream3 ("?????", StreamLanguage::PT_PT, 10, StreamGenre::COOKING, std::make_shared<Streamer>(streamer2), 50);
    auto stream1_ptr = std::dynamic_pointer_cast<Stream>(std::make_shared<PublicStream>(stream1));
    Viewer viewer1(birthDate2,"Visualizador Não Pog","Pogn't", "adknjsada");
    Viewer viewer2(birthDate1,"Visualizador Pog","Pog", "hjkoasiodhnoaisd");
    auto viewer1_ptr = std::make_shared<Viewer>(viewer1);
    auto viewer2_ptr = std::make_shared<Viewer>(viewer2);
    if(stream1.canJoin(viewer1_ptr)) { viewer1_ptr->joinStream(stream1_ptr); }
    if(stream1.canJoin(viewer2_ptr)) { viewer2_ptr->joinStream(stream1_ptr); }
    EXPECT_EQ(stream1.getNumOfViewers(), 2);
    EXPECT_EQ(stream3.getNumOfViews(), 50);
    viewer1.leaveCurrentStream();
    EXPECT_EQ(stream1.getNumOfViewers(), 1);
    EXPECT_EQ(stream2.getNumOfViewers(), 0);
}

TEST(stream, getMinAge){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "sentiatensao");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "muitofixemeu");
    PublicStream stream1("Epic LoL Stream", StreamLanguage::EN, 13, StreamGenre::GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", StreamLanguage::EN, 18, StreamGenre::GAMING, std::make_shared<Streamer>(streamer2));
    FinishedStream stream3 ("?????", StreamLanguage::PT_PT, 10, StreamGenre::COOKING, std::make_shared<Streamer>(streamer2), 50);
    EXPECT_EQ(stream1.getMinAge(), 13);
    EXPECT_EQ(stream2.getMinAge(), 18);
    EXPECT_EQ(stream3.getMinAge(), 10);
}

TEST(stream, getTitle){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "muitofixemeu");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "homembase");
    PublicStream stream1("Epic LoL Stream", StreamLanguage::EN, 13, StreamGenre::GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", StreamLanguage::EN, 18, StreamGenre::GAMING, std::make_shared<Streamer>(streamer2));
    FinishedStream stream3 ("?????", StreamLanguage::PT_PT, 10, StreamGenre::COOKING, std::make_shared<Streamer>(streamer2), 50);
    EXPECT_EQ(stream1.getTitle(), "Epic LoL Stream");
    EXPECT_EQ(stream2.getTitle(), "Based Games");
    EXPECT_EQ(stream3.getTitle(), "?????");
}

TEST(stream, getLanguage){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "eusouautofeito");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "olaoscra");
    PublicStream stream1("Epic LoL Stream", StreamLanguage::EN, 13, StreamGenre::GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", StreamLanguage::RU, 18, StreamGenre::GAMING, std::make_shared<Streamer>(streamer2));
    FinishedStream stream3 ("?????", StreamLanguage::PT_PT, 10, StreamGenre::COOKING, std::make_shared<Streamer>(streamer2), 50);
    EXPECT_EQ(stream1.getLanguage(), StreamLanguage::EN);
    EXPECT_EQ(stream2.getLanguage(), StreamLanguage::RU);
    EXPECT_EQ(stream3.getLanguage(), StreamLanguage::PT_PT);
}

TEST(stream, getStreamDate){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "olaoscra");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "euvoulevarmute");
    PublicStream stream1("Epic LoL Stream", StreamLanguage::EN, 13, StreamGenre::GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", StreamLanguage::EN, 18, StreamGenre::GAMING, std::make_shared<Streamer>(streamer2));
    FinishedStream stream3 ("?????", StreamLanguage::PT_PT, 10, StreamGenre::COOKING, std::make_shared<Streamer>(streamer2), 50);
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
    PublicStream stream1("Epic LoL Stream", StreamLanguage::EN, 13, StreamGenre::GAMING, streamer1_ptr);
    PrivateStream stream2("Based Games", StreamLanguage::EN, 18, StreamGenre::GAMING, streamer2_ptr);
    FinishedStream stream3 ("?????", StreamLanguage::PT_PT, 10, StreamGenre::COOKING, streamer2_ptr, 50);
    EXPECT_EQ(stream1.getStreamer(), streamer1_ptr);
    EXPECT_EQ(stream2.getStreamer(), streamer2_ptr);
    EXPECT_EQ(stream3.getStreamer(), streamer2_ptr);
}

TEST(stream, getGenre){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "sintoatensao");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "algosepassa");
    PublicStream stream1("Epic LoL Stream", StreamLanguage::EN, 13, StreamGenre::GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", StreamLanguage::EN, 18, StreamGenre::TALKSHOW, std::make_shared<Streamer>(streamer2));
    FinishedStream stream3 ("?????", StreamLanguage::PT_PT, 10, StreamGenre::COOKING, std::make_shared<Streamer>(streamer2), 50);
    PrivateStream stream4("Top Hits 1857", StreamLanguage::ES, 3, StreamGenre::MUSIC, std::make_shared<Streamer>(streamer1));
    EXPECT_EQ(stream1.getGenre(), StreamGenre::GAMING);
    EXPECT_EQ(stream2.getGenre(), StreamGenre::TALKSHOW);
    EXPECT_EQ(stream3.getGenre(), StreamGenre::COOKING);
    EXPECT_EQ(stream4.getGenre(), StreamGenre::MUSIC);
}

/* Só funciona se for corrido isoladamente!
TEST(stream, getUniqueID){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base");
    PublicStream stream1("Epic LoL Stream", EN, 13, GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", EN, 18, TALKSHOW, std::make_shared<Streamer>(streamer2));
    FinishedStream stream3 ("?????", PT_PT, 10, COOKING, std::make_shared<Streamer>(streamer2), 50);
    PrivateStream stream4("Top Hits 1857", ES, 3, MUSIC, std::make_shared<Streamer>(streamer1));
    EXPECT_EQ(stream1.getUniqueId(), 1);
    EXPECT_EQ(stream2.getUniqueId(), 2);
    EXPECT_EQ(stream3.getUniqueId(), 3);
    EXPECT_EQ(stream4.getUniqueId(), 4);
}
*/

TEST(stream, addFeedback){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "123ola123");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "baseado890");
    PublicStream stream1("Epic LoL Stream", StreamLanguage::EN, 13, StreamGenre::GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", StreamLanguage::EN, 18, StreamGenre::GAMING, std::make_shared<Streamer>(streamer2));
    FinishedStream stream3 ("?????", StreamLanguage::PT_PT, 10, StreamGenre::COOKING, std::make_shared<Streamer>(streamer2), 50);
    stream1.addFeedback(FeedbackLikeSystem::LIKE);
    stream1.addFeedback(FeedbackLikeSystem::LIKE);
    stream1.addFeedback(FeedbackLikeSystem::LIKE);
    stream1.addFeedback(FeedbackLikeSystem::DISLIKE);
    stream2.addFeedback(FeedbackLikeSystem::DISLIKE);
    stream2.addFeedback(FeedbackLikeSystem::DISLIKE);
    stream3.addFeedback(FeedbackLikeSystem::LIKE);
    stream3.addFeedback(FeedbackLikeSystem::DISLIKE);
    stream3.addFeedback(FeedbackLikeSystem::INVALID_VOTE);
    EXPECT_EQ(stream1.getVotes().first, 3);
    EXPECT_EQ(stream1.getVotes().second, 1);
    EXPECT_EQ(stream2.getVotes().first, 0);
    EXPECT_EQ(stream2.getVotes().second, 2);
    EXPECT_EQ(stream3.getVotes().first, 1);
    EXPECT_EQ(stream3.getVotes().second, 1);
}
