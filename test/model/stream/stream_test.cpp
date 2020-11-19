//
// Created by Danny on 03/11/2020.
//

#include <gtest/gtest.h>
#include <model/stream/stream.h>
#include <model/stream/privateStream/privateStream.h>
#include <model/stream/publicStream/publicStream.h>
#include <model/stream/finishedStream/finishedStream.h>
#include <model/user/streamer/streamer.h>
#include <model/user/user_manager.h>
#include <model/user/viewer/viewer_manager.h>
#include <model/stream/streamManager.h>
#include <model/user/streamer/streamer_manager.h>
#include <exception/invalidFeedback/invalidFeedback.h>


using testing::Eq;

TEST(stream, getNumOfViewers){
    std::shared_ptr<UserManager> um1 =  std::make_shared<UserManager>();
    std::shared_ptr<ViewerManager> vm1 = std::make_shared<ViewerManager>(um1);
    std::shared_ptr<StreamManager> sm1 = std::make_shared<StreamManager>(vm1, std::make_shared<StreamerManager>());
    std::shared_ptr<StreamerManager> stm1 = std::make_shared<StreamerManager>(sm1,vm1,um1);
    sm1->setStreamerManager(stm1);
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "olaamego");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "muitofixemeu");
    auto stream1 = std::dynamic_pointer_cast<PublicStream>(sm1->build("Epic LoL Stream", StreamLanguage::EN, 13, StreamType::PUBLIC, StreamGenre::GAMING, std::make_shared<Streamer>(streamer1)));
    auto stream2 = std::dynamic_pointer_cast<PrivateStream>(sm1->build("Based Games", StreamLanguage::EN, 18,  StreamType::PRIVATE, StreamGenre::GAMING, std::make_shared<Streamer>(streamer2)));
    auto viewer1 = vm1->build(birthDate2,"Visualizador Não Pog","Pogn't", "adknjsada");
    auto viewer2 = vm1->build(birthDate1,"Visualizador Pog","Pog", "hjkoasiodhnoaisd");
    viewer1->joinStream(stream1);
    viewer2->joinStream(stream1);
    EXPECT_EQ(stream1->getNumOfViewers(), 2);
    viewer1->leaveCurrentStream();
    EXPECT_EQ(stream1->getNumOfViewers(), 1);
    EXPECT_EQ(stream2->getNumOfViewers(), 0);
    auto finished1 = sm1->finish(stream1);
    EXPECT_EQ(finished1->getNumOfViews(), 1);
}

TEST(stream, getMinAge){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "sentiatensao");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "muitofixemeu");
    PublicStream stream1("Epic LoL Stream", StreamLanguage::EN, 13, StreamGenre::GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", StreamLanguage::EN, 18, StreamGenre::GAMING, std::make_shared<Streamer>(streamer2));
    EXPECT_EQ(stream1.getMinAge(), 13);
    EXPECT_EQ(stream2.getMinAge(), 18);
}

TEST(stream, getTitle){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "muitofixemeu");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "homembase");
    PublicStream stream1("Epic LoL Stream", StreamLanguage::EN, 13, StreamGenre::GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", StreamLanguage::EN, 18, StreamGenre::GAMING, std::make_shared<Streamer>(streamer2));
    EXPECT_EQ(stream1.getTitle(), "Epic LoL Stream");
    EXPECT_EQ(stream2.getTitle(), "Based Games");
}

TEST(stream, getLanguage){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "eusouautofeito");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "olaoscra");
    PublicStream stream1("Epic LoL Stream", StreamLanguage::EN, 13, StreamGenre::GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", StreamLanguage::RU, 18, StreamGenre::GAMING, std::make_shared<Streamer>(streamer2));
    EXPECT_EQ(stream1.getLanguage(), StreamLanguage::EN);
    EXPECT_EQ(stream2.getLanguage(), StreamLanguage::RU);
}

TEST(stream, getStreamer){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "cheirameabase");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "muitofixemeu");
    std::shared_ptr<Streamer> streamer1_ptr = std::make_shared<Streamer>(streamer1);
    std::shared_ptr<Streamer> streamer2_ptr = std::make_shared<Streamer>(streamer2);
    PublicStream stream1("Epic LoL Stream", StreamLanguage::EN, 13, StreamGenre::GAMING, streamer1_ptr);
    PrivateStream stream2("Based Games", StreamLanguage::EN, 18, StreamGenre::GAMING, streamer2_ptr);
    EXPECT_EQ(stream1.getStreamer(), streamer1_ptr);
    EXPECT_EQ(stream2.getStreamer(), streamer2_ptr);
}

TEST(stream, getGenre){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "sintoatensao");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "algosepassa");
    PublicStream stream1("Epic LoL Stream", StreamLanguage::EN, 13, StreamGenre::GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", StreamLanguage::EN, 18, StreamGenre::TALKSHOW, std::make_shared<Streamer>(streamer2));
    PublicStream stream3 ("?????", StreamLanguage::PT_PT, 10, StreamGenre::COOKING, std::make_shared<Streamer>(streamer2));
    PrivateStream stream4("Top Hits 1857", StreamLanguage::ES, 3, StreamGenre::MUSIC, std::make_shared<Streamer>(streamer1));
    EXPECT_EQ(stream1.getGenre(), StreamGenre::GAMING);
    EXPECT_EQ(stream2.getGenre(), StreamGenre::TALKSHOW);
    EXPECT_EQ(stream3.getGenre(), StreamGenre::COOKING);
    EXPECT_EQ(stream4.getGenre(), StreamGenre::MUSIC);
}

/* Só funciona se for corrido isoladamente!
TEST(stream, getUniqueID){
    std::shared_ptr<UserManager> um1 =  std::make_shared<UserManager>();
    std::shared_ptr<ViewerManager> vm1 = std::make_shared<ViewerManager>(um1);
    std::shared_ptr<StreamManager> sm1 = std::make_shared<StreamManager>(vm1, std::make_shared<StreamerManager>());
    std::shared_ptr<StreamerManager> stm1 = std::make_shared<StreamerManager>(sm1,vm1,um1);
    sm1->setStreamerManager(stm1);
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    auto streamer1 = stm1->build(birthDate1, "Oskar ÚltimoNome", "Autofeito", "wersfgdfg");
    auto streamer2 = stm1->build(birthDate2, "Homem Baseado", "Base", "dsfghjkj");
    auto streamer3 = stm1->build(birthDate2, "Homem Baseado 2", "Base 2", "dsfghjkj2");
    auto stream1 = sm1->build("Epic LoL Stream", StreamLanguage::EN, 13, StreamType::PRIVATE, StreamGenre::GAMING, streamer1);
    auto stream2 = sm1->build("Based Games", StreamLanguage::AF, 18,StreamType::PRIVATE, StreamGenre::TALKSHOW, streamer2);
    auto stream3 = sm1->build("Top Hits 1857", StreamLanguage::ES, 3, StreamType::PUBLIC, StreamGenre::MUSIC, streamer3);
    EXPECT_EQ(stream1->getUniqueId(), 1);
    EXPECT_EQ(stream2->getUniqueId(), 2);
    EXPECT_EQ(stream3->getUniqueId(), 3);
    auto finished1 = sm1->finish(stream1);
    EXPECT_EQ(finished1->getID(), 1);
} */

TEST(stream, addFeedback){
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito", "123ola123");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base", "baseado890");
    PublicStream stream1("Epic LoL Stream", StreamLanguage::EN, 13, StreamGenre::GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", StreamLanguage::EN, 18, StreamGenre::GAMING, std::make_shared<Streamer>(streamer2));
    PrivateStream stream3 ("?????", StreamLanguage::PT_PT, 10, StreamGenre::COOKING, std::make_shared<Streamer>(streamer2));
    stream1.addFeedback("marco",FeedbackLikeSystem::LIKE);
    stream1.addFeedback("marco1",FeedbackLikeSystem::LIKE);
    stream1.addFeedback("marco2",FeedbackLikeSystem::LIKE);
    stream1.addFeedback("marco3",FeedbackLikeSystem::DISLIKE);
    stream2.addFeedback("marco4",FeedbackLikeSystem::DISLIKE);
    stream2.addFeedback("marco5",FeedbackLikeSystem::DISLIKE);
    stream3.addFeedback("marco6",FeedbackLikeSystem::LIKE);
    stream3.addFeedback("marco7",FeedbackLikeSystem::DISLIKE);
    EXPECT_THROW(stream3.addFeedback("marco8",FeedbackLikeSystem::INVALID_VOTE), InvalidFeedback);
    try {
        stream3.addFeedback("marco8",FeedbackLikeSystem::INVALID_VOTE);
    }
    catch (InvalidFeedback &e) {
        EXPECT_EQ(e.getMessage(), "You can only LIKE or DISLIKE a stream!");
    }
    EXPECT_EQ(stream1.getVotes().first, 3);
    EXPECT_EQ(stream1.getVotes().second, 1);
    EXPECT_EQ(stream2.getVotes().first, 0);
    EXPECT_EQ(stream2.getVotes().second, 2);
    EXPECT_EQ(stream3.getVotes().first, 1);
    EXPECT_EQ(stream3.getVotes().second, 1);
}
