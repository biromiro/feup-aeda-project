//
// Created by Danny on 08/11/2020.
//

#include <gtest/gtest.h>
#include <stream/stream.h>
#include <stream/privateStream/privateStream.h>
#include <stream/publicStream/publicStream.h>
#include <stream/finishedStream/finishedStream.h>
#include <user/streamer/streamer.h>
#include <user/viewer/viewer_manager.h>
#include <stream/streamManager.h>
#include <user/streamer/streamer_manager.h>

using testing::Eq;

TEST(streamManager, build){
    std::shared_ptr<UserManager> um1 =  std::make_shared<UserManager>();
    std::shared_ptr<ViewerManager> vm1 = std::make_shared<ViewerManager>(um1);
    std::shared_ptr<StreamManager> sm1 = std::make_shared<StreamManager>(vm1, std::make_shared<StreamerManager>());
    std::shared_ptr<StreamerManager>srm1 = std::make_shared<StreamerManager>(sm1, vm1, um1);
    sm1->setStreamerManager(srm1);
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base");
    auto streamer1_ptr = std::make_shared<Streamer> (streamer1);
    auto streamer2_ptr = std::make_shared<Streamer> (streamer2);
    auto stream1 = sm1->build("Epic LoL Stream", EN, 13, PUBLIC, GAMING, streamer1_ptr);
    auto stream2 = sm1->build("Based Games", RU, 18, PRIVATE, MUSIC, streamer2_ptr);
    EXPECT_EQ(sm1->build("Based Games Null Ptr", PT_BR, 16, PRIVATE, GAMING, streamer2_ptr), nullptr);
    EXPECT_EQ(stream1->getTitle(), "Epic LoL Stream");
    EXPECT_EQ(stream2->getTitle(), "Based Games");
    EXPECT_EQ(stream1->getLanguage(), EN);
    EXPECT_EQ(stream2->getLanguage(), RU);
    EXPECT_EQ(stream1->getMinAge(), 13);
    EXPECT_EQ(stream2->getMinAge(), 18);
    EXPECT_EQ(stream1->getStreamType(), PUBLIC);
    EXPECT_EQ(stream2->getStreamType(), PRIVATE);
    EXPECT_EQ(stream1->getGenre(), GAMING);
    EXPECT_EQ(stream2->getGenre(), MUSIC);
    EXPECT_EQ(stream1->getStreamer(), streamer1_ptr);
    EXPECT_EQ(stream2->getStreamer(), streamer2_ptr);
}

TEST(streamManager, streams_vector_methods){
    std::shared_ptr<UserManager> um1 =  std::make_shared<UserManager>();
    std::shared_ptr<ViewerManager> vm1 = std::make_shared<ViewerManager>(um1);
    StreamManager sm1(vm1, std::make_shared<StreamerManager>());
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base");
    PublicStream stream1("Epic LoL Stream", EN, 13, GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", EN, 18, GAMING, std::make_shared<Streamer>(streamer2));
    std::shared_ptr<PublicStream> stream1_ptr = std::make_shared<PublicStream>(stream1);
    std::shared_ptr<PrivateStream> stream2_ptr = std::make_shared<PrivateStream>(stream2);
    sm1.add(stream1_ptr);
    sm1.add(stream2_ptr);
    std::vector<std::shared_ptr<Stream>> expect_streams1 = {stream1_ptr, stream2_ptr};
    EXPECT_EQ(sm1.getStreams(), expect_streams1);
    sm1.remove(stream2_ptr);
    std::vector<std::shared_ptr<Stream>> expect_streams2 = {stream1_ptr};
    EXPECT_EQ(sm1.getStreams(), expect_streams2);
    EXPECT_EQ(sm1.has(stream1_ptr), true);
    EXPECT_EQ(sm1.has(stream2_ptr), false);
}
/* Só funciona isoladamente!
TEST(streamManager, get){
    std::shared_ptr<UserManager> um1 =  std::make_shared<UserManager>();
    std::shared_ptr<ViewerManager> vm1 = std::make_shared<ViewerManager>(um1);
    StreamManager sm1(vm1, std::make_shared<StreamerManager>());
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base");
    PublicStream stream1("Epic LoL Stream", EN, 13, GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", EN, 18, GAMING, std::make_shared<Streamer>(streamer2));
    std::shared_ptr<PublicStream> stream1_ptr = std::make_shared<PublicStream>(stream1);
    std::shared_ptr<PrivateStream> stream2_ptr = std::make_shared<PrivateStream>(stream2);
    sm1.add(stream1_ptr);
    sm1.add(stream2_ptr);
    EXPECT_EQ(sm1.get(1), stream1_ptr);
    EXPECT_EQ(sm1.get(2), stream2_ptr);
    EXPECT_EQ(sm1.get(3), nullptr);
}*/

TEST(streamManager, finish){
    std::shared_ptr<UserManager> um1 =  std::make_shared<UserManager>();
    std::shared_ptr<ViewerManager> vm1 = std::make_shared<ViewerManager>(um1);
    StreamManager sm1(vm1, std::make_shared<StreamerManager>());
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base");
    Streamer streamer3(birthDate2, "Generic Streamer", "GS");
    PublicStream stream1("Epic LoL Stream", EN, 13, GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", EN, 18, GAMING, std::make_shared<Streamer>(streamer2));
    FinishedStream stream3 ("?????", PT_PT, 10, COOKING, std::make_shared<Streamer>(streamer3), 50);
    std::shared_ptr<PublicStream> stream1_ptr = std::make_shared<PublicStream>(stream1);
    std::shared_ptr<PrivateStream> stream2_ptr = std::make_shared<PrivateStream>(stream2);
    std::shared_ptr<FinishedStream> stream3_ptr = std::make_shared<FinishedStream>(stream3);
    Viewer viewer1(birthDate2,"Visualizador Não Pog","Pogn't");
    std::shared_ptr<Viewer> viewer1_ptr = std::make_shared<Viewer>(viewer1);
    viewer1_ptr->joinStream(stream1_ptr);
    EXPECT_EQ(viewer1_ptr->isWatchingStream(), true);
    EXPECT_EQ(sm1.finish(stream3_ptr), nullptr);
    auto finished_stream1 = std::dynamic_pointer_cast<Stream>(sm1.finish(stream1_ptr));
    auto finished_stream2 = std::dynamic_pointer_cast<Stream>(sm1.finish(stream2_ptr));
    std::vector<std::shared_ptr<Stream>> expect_streams1 = {finished_stream1, finished_stream2};
    EXPECT_EQ(sm1.getCacheOfFinishedStreams(), expect_streams1);
    EXPECT_EQ(finished_stream1->getStreamType(), FINISHED);
    EXPECT_EQ(finished_stream2->getStreamType(), FINISHED);
    EXPECT_EQ(std::dynamic_pointer_cast<FinishedStream>(finished_stream1)->getNumOfViews(), 1);
    EXPECT_EQ(std::dynamic_pointer_cast<FinishedStream>(finished_stream2)->getNumOfViews(), 0);
    EXPECT_EQ(viewer1_ptr->isWatchingStream(), false);
}

TEST(streamManager, getNumOfViewers){
    std::shared_ptr<UserManager> um1 =  std::make_shared<UserManager>();
    std::shared_ptr<ViewerManager> vm1 = std::make_shared<ViewerManager>(um1);
    StreamManager sm1(vm1, std::make_shared<StreamerManager>());
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26"), birthDate3("1996/04/02");
    Streamer streamer1(birthDate1, "Oskar ÚltimoNome", "Autofeito");
    Streamer streamer2(birthDate2, "Homem Baseado", "Base");
    Viewer viewer1(birthDate2,"Visualizador Não Pog","Pogn't");
    Viewer viewer2(birthDate1,"Visualizador Pog","Pog");
    Viewer viewer3(birthDate3,"Visualizador Pog 2","Pog 2");
    PublicStream stream1("Epic LoL Stream", EN, 13, GAMING, std::make_shared<Streamer>(streamer1));
    PrivateStream stream2("Based Games", EN, 18, GAMING, std::make_shared<Streamer>(streamer2));
    std::shared_ptr<PublicStream> stream1_ptr = std::make_shared<PublicStream>(stream1);
    std::shared_ptr<PrivateStream> stream2_ptr = std::make_shared<PrivateStream>(stream2);
    std::shared_ptr<Viewer> viewer1_ptr = std::make_shared<Viewer>(viewer1);
    std::shared_ptr<Viewer> viewer2_ptr = std::make_shared<Viewer>(viewer2);
    std::shared_ptr<Viewer> viewer3_ptr = std::make_shared<Viewer>(viewer3);
    stream2.addToWhitelist(viewer1_ptr);
    stream2.addToWhitelist(viewer2_ptr);
    if(stream1.canJoin(std::make_shared<Viewer>(viewer1))) { viewer1_ptr->joinStream(stream1_ptr); }
    if(stream1.canJoin(std::make_shared<Viewer>(viewer1))) { viewer1_ptr->joinStream(stream2_ptr); }
    if(stream1.canJoin(std::make_shared<Viewer>(viewer2))) { viewer2_ptr->joinStream(stream2_ptr); }
    EXPECT_EQ(sm1.getNumOfViewers(stream1_ptr), 1);
    if(stream1.canJoin(std::make_shared<Viewer>(viewer3))) { viewer3_ptr->joinStream(stream1_ptr); }
    EXPECT_EQ(sm1.getNumOfViewers(stream1_ptr), 1);
    EXPECT_EQ(sm1.getNumOfViewers(stream2_ptr), 2);
}