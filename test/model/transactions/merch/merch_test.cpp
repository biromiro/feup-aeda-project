//
// Created by Danny on 21/12/2020.
//

#include <gtest/gtest.h>
#include <model/transactions/merch/merchRequest.h>
#include <model/user/streamer/streamer.h>
#include <model/user/user_manager.h>
#include <model/user/viewer/viewer_manager.h>
#include <model/stream/streamManager.h>
#include <model/user/streamer/streamer_manager.h>
#include <model/user/admin/admin_manager.h>
#include <exception/orderLimitReached/orderLimitReached.h>
#include <exception/invalidPurchaseAvailability/invalidPurchaseAvailability.h>
#include <exception/viewerAlreadyOrdered/viewerAlreadyOrdered.h>
#include <exception/orderNotFound/orderNotFound.h>

using testing::Eq;

TEST(merch, setUpMerch) {
    std::shared_ptr<UserManager> um1 =  std::make_shared<UserManager>();
    std::shared_ptr<AdminManager> am1 = std::make_shared<AdminManager>(um1);
    std::shared_ptr<ViewerManager> vm1 = std::make_shared<ViewerManager>(um1);
    std::shared_ptr<StreamManager> sm1 = std::make_shared<StreamManager>(vm1, std::make_shared<StreamerManager>());
    std::shared_ptr<StreamerManager> stm1 = std::make_shared<StreamerManager>(sm1,vm1,um1);
    sm1->setStreamerManager(stm1);
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    auto streamer1 = stm1->build(birthDate1, "Oskar ÚltimoNome", "Autofeito", "jknadjkhnasida");
    auto streamer2 = stm1->build(birthDate2, "Homem Baseado", "Base", "knajkodhnaisda");
    am1->setMerchLimit(20);
    streamer1->setUpMerch(am1->getMerchLimit());
    EXPECT_EQ(streamer1->getStreamerMerch().getLimit(), 20);
    EXPECT_EQ(streamer2->getStreamerMerch().getLimit(), 0);
    EXPECT_EQ(streamer1->getStreamerMerch().getOrders().size(), 0);
    EXPECT_EQ(streamer2->getStreamerMerch().getOrders().size(), 0);
}

TEST(merch, addOrder) {
    std::shared_ptr<UserManager> um1 =  std::make_shared<UserManager>();
    std::shared_ptr<AdminManager> am1 = std::make_shared<AdminManager>(um1);
    std::shared_ptr<ViewerManager> vm1 = std::make_shared<ViewerManager>(um1);
    std::shared_ptr<StreamManager> sm1 = std::make_shared<StreamManager>(vm1, std::make_shared<StreamerManager>());
    std::shared_ptr<StreamerManager> stm1 = std::make_shared<StreamerManager>(sm1,vm1,um1);
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    auto streamer1 = stm1->build(birthDate1, "Oskar ÚltimoNome", "Autofeito", "jknadjkhnasida");
    auto streamer2 = stm1->build(birthDate2, "Homem Baseado", "Base", "knajkodhnaisda");
    auto viewer1 = vm1->build(birthDate2,"Visualizador Não Pog","Pogn't", "adknjsada");
    auto viewer2 = vm1->build(birthDate1,"Visualizador Pog","Pog", "hjkoasiodhnoaisd");
    EXPECT_THROW(viewer1->orderMerch(streamer1, 5, 1), OrderLimitReached);
    am1->setMerchLimit(20);
    streamer1->setUpMerch(am1->getMerchLimit());
    streamer2->setUpMerch(am1->getMerchLimit());
    EXPECT_THROW(viewer1->orderMerch(streamer1, 5, 6), InvalidPurchaseAvailability);
    viewer1->orderMerch(streamer1, 20, 3);
    viewer1->orderMerch(streamer2, 4, 1);
    viewer2->orderMerch(streamer2, 10, 2);
    EXPECT_THROW(viewer1->orderMerch(streamer1, 5, 4), ViewerAlreadyOrdered);
    EXPECT_EQ(streamer1->getStreamerMerch().getOrders().size(), 1);
    EXPECT_EQ(streamer2->getStreamerMerch().getOrders().size(), 2);
}

TEST(merch, removeOrder) {
    std::shared_ptr<UserManager> um1 =  std::make_shared<UserManager>();
    std::shared_ptr<AdminManager> am1 = std::make_shared<AdminManager>(um1);
    std::shared_ptr<ViewerManager> vm1 = std::make_shared<ViewerManager>(um1);
    std::shared_ptr<StreamManager> sm1 = std::make_shared<StreamManager>(vm1, std::make_shared<StreamerManager>());
    std::shared_ptr<StreamerManager> stm1 = std::make_shared<StreamerManager>(sm1,vm1,um1);
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    auto streamer1 = stm1->build(birthDate1, "Oskar ÚltimoNome", "Autofeito", "jknadjkhnasida");
    auto streamer2 = stm1->build(birthDate2, "Homem Baseado", "Base", "knajkodhnaisda");
    auto viewer1 = vm1->build(birthDate2,"Visualizador Não Pog","Pogn't", "adknjsada");
    auto viewer2 = vm1->build(birthDate1,"Visualizador Pog","Pog", "hjkoasiodhnoaisd");
    am1->setMerchLimit(20);
    streamer1->setUpMerch(am1->getMerchLimit());
    streamer2->setUpMerch(am1->getMerchLimit());
    viewer1->orderMerch(streamer1, 20, 3);
    viewer1->orderMerch(streamer2, 4, 1);
    viewer2->orderMerch(streamer2, 10, 2);
    viewer1->removeOrder(streamer1);
    viewer1->removeOrder(streamer2);
    EXPECT_EQ(streamer1->getStreamerMerch().getOrders().size(), 0);
    EXPECT_EQ(streamer2->getStreamerMerch().getOrders().size(), 1);
    EXPECT_THROW(viewer1->removeOrder(streamer1), OrderNotFound);
    EXPECT_THROW(viewer2->removeOrder(streamer1), OrderNotFound);
}

TEST(merch, processOrder) {
    std::shared_ptr<UserManager> um1 =  std::make_shared<UserManager>();
    std::shared_ptr<AdminManager> am1 = std::make_shared<AdminManager>(um1);
    std::shared_ptr<ViewerManager> vm1 = std::make_shared<ViewerManager>(um1);
    std::shared_ptr<StreamManager> sm1 = std::make_shared<StreamManager>(vm1, std::make_shared<StreamerManager>());
    std::shared_ptr<StreamerManager> stm1 = std::make_shared<StreamerManager>(sm1,vm1,um1);
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    auto streamer1 = stm1->build(birthDate1, "Oskar ÚltimoNome", "Autofeito", "jknadjkhnasida");
    auto streamer2 = stm1->build(birthDate2, "Homem Baseado", "Base", "knajkodhnaisda");
    auto viewer1 = vm1->build(birthDate2,"Visualizador Não Pog","Pogn't", "adknjsada");
    auto viewer2 = vm1->build(birthDate1,"Visualizador Pog","Pog", "hjkoasiodhnoaisd");
    am1->setMerchLimit(20);
    streamer1->setUpMerch(am1->getMerchLimit());
    streamer2->setUpMerch(am1->getMerchLimit());
    viewer1->orderMerch(streamer1, 20, 3);
    viewer2->orderMerch(streamer2, 10, 2);
    viewer1->orderMerch(streamer2, 4, 1);
    auto nextOrder = streamer2->processNextOrder();
    EXPECT_EQ(nextOrder.getPurchaseA(), 1);
    EXPECT_EQ(nextOrder.getBuyer(), viewer1->getName());
    EXPECT_EQ(nextOrder.getQuantity(), 4);
    nextOrder = streamer1->processNextOrder();
    EXPECT_EQ(streamer1->getStreamerMerch().getOrders().size(), 0);
    EXPECT_EQ(streamer2->getStreamerMerch().getOrders().size(), 1);
    nextOrder = streamer2->processNextOrder();
    EXPECT_EQ(streamer2->getStreamerMerch().getOrders().size(), 0);
}

TEST(merch, ordersQueue) {
    std::shared_ptr<UserManager> um1 =  std::make_shared<UserManager>();
    std::shared_ptr<AdminManager> am1 = std::make_shared<AdminManager>(um1);
    std::shared_ptr<ViewerManager> vm1 = std::make_shared<ViewerManager>(um1);
    std::shared_ptr<StreamManager> sm1 = std::make_shared<StreamManager>(vm1, std::make_shared<StreamerManager>());
    std::shared_ptr<StreamerManager> stm1 = std::make_shared<StreamerManager>(sm1,vm1,um1);
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    auto streamer1 = stm1->build(birthDate1, "Oskar ÚltimoNome", "Autofeito", "jknadjkhnasida");
    auto viewer1 = vm1->build(birthDate2,"Visualizador Não Pog","Pogn't", "adknjsada");
    auto viewer2 = vm1->build(birthDate1,"Visualizador Pog","Pog", "hjkoasiodhnoaisd");
    auto viewer3 = vm1->build(birthDate1,"Visualizador Pog 2","Pog2", "hjkoasiodhnoaisd2");
    am1->setMerchLimit(20);
    streamer1->setUpMerch(am1->getMerchLimit());
    viewer1->orderMerch(streamer1, 20, 4);
    viewer2->orderMerch(streamer1, 10, 2);
    viewer3->orderMerch(streamer1, 10, 3);
    auto nextOrder = streamer1->processNextOrder();
    EXPECT_EQ(nextOrder.getPurchaseA(), 3);
    EXPECT_EQ(nextOrder.getBuyer(), viewer3->getName());
    EXPECT_EQ(nextOrder.getQuantity(), 10);
    nextOrder = streamer1->processNextOrder();
    EXPECT_EQ(nextOrder.getPurchaseA(), 2);
    EXPECT_EQ(nextOrder.getBuyer(), viewer2->getName());
    EXPECT_EQ(nextOrder.getQuantity(), 10);
    nextOrder = streamer1->processNextOrder();
    EXPECT_EQ(nextOrder.getPurchaseA(), 4);
    EXPECT_EQ(nextOrder.getBuyer(), viewer1->getName());
    EXPECT_EQ(nextOrder.getQuantity(), 20);
}

TEST(merch, queueLimit) {
    std::shared_ptr<UserManager> um1 =  std::make_shared<UserManager>();
    std::shared_ptr<AdminManager> am1 = std::make_shared<AdminManager>(um1);
    std::shared_ptr<ViewerManager> vm1 = std::make_shared<ViewerManager>(um1);
    std::shared_ptr<StreamManager> sm1 = std::make_shared<StreamManager>(vm1, std::make_shared<StreamerManager>());
    std::shared_ptr<StreamerManager> stm1 = std::make_shared<StreamerManager>(sm1,vm1,um1);
    Date birthDate1("1999/06/09"), birthDate2("2000/02/26");
    auto streamer1 = stm1->build(birthDate1, "Oskar ÚltimoNome", "Autofeito", "jknadjkhnasida");
    auto viewer1 = vm1->build(birthDate2,"Visualizador Não Pog","Pogn't", "adknjsada");
    auto viewer2 = vm1->build(birthDate1,"Visualizador Pog","Pog", "hjkoasiodhnoaisd");
    auto viewer3 = vm1->build(birthDate1,"Visualizador Pog 2","Pog2", "hjkoasiodhnoaisd2");
    am1->setMerchLimit(3);
    streamer1->setUpMerch(am1->getMerchLimit());
    viewer1->orderMerch(streamer1, 20, 4);
    viewer2->orderMerch(streamer1, 10, 2);
    viewer3->orderMerch(streamer1, 10, 3);
    am1->setMerchLimit(2);
    streamer1->updateMerchLimit(am1->getMerchLimit());
    EXPECT_EQ(streamer1->getStreamerMerch().getOrders().size(), 2);
    auto nextOrder = streamer1->processNextOrder();
    EXPECT_EQ(nextOrder.getPurchaseA(), 3);
    EXPECT_EQ(nextOrder.getBuyer(), viewer3->getName());
    EXPECT_EQ(nextOrder.getQuantity(), 10);
    nextOrder = streamer1->processNextOrder();
    EXPECT_EQ(nextOrder.getPurchaseA(), 2);
    EXPECT_EQ(nextOrder.getBuyer(), viewer2->getName());
    EXPECT_EQ(nextOrder.getQuantity(), 10);
    EXPECT_EQ(streamer1->getStreamerMerch().getOrders().size(), 0);
}
