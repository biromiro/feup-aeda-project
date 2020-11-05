//
// Created by biromiro on 01/11/20.
//

#include <gtest/gtest.h>
#include <user/viewer/viewer_manager.h>

using testing::Eq;


TEST(viewer_manager, build_add){
    std::shared_ptr<UserManager> userManager =  std::make_shared<UserManager>();
    ViewerManager viewerManager = ViewerManager(userManager);
    Date birthDate("2001/10/20");
    EXPECT_EQ(viewerManager.getViewers().size(), 0);
    EXPECT_EQ(viewerManager.build(birthDate, "Nuno Costa", "biromiro") != nullptr, true);
    EXPECT_EQ(viewerManager.getViewers().size(), 1);
    EXPECT_EQ(viewerManager.build(birthDate, "Pedro Costa", "biromiro"), nullptr);
}

TEST(viewer_manager, remove){
    std::shared_ptr<UserManager> userManager =  std::make_shared<UserManager>();
    ViewerManager viewerManager = ViewerManager(userManager);
    Date birthDate("2001/10/20");
    EXPECT_EQ(viewerManager.getViewers().size(), 0);
    auto viewer1 = viewerManager.build(birthDate, "Nuno Costa", "biromiro");
    EXPECT_EQ(viewerManager.getViewers().size(), 1);
    EXPECT_EQ(viewerManager.remove(viewer1), true);
    EXPECT_EQ(viewerManager.remove(viewer1), false);
    EXPECT_EQ(viewerManager.getViewers().size(), 0);
}

TEST(viewer_manager, has){
    std::shared_ptr<UserManager> userManager =  std::make_shared<UserManager>();
    ViewerManager viewerManager = ViewerManager(userManager);
    Date birthDate("2001/10/20");
    EXPECT_EQ(viewerManager.has("biromiro"),false);
    auto viewer1 = viewerManager.build(birthDate, "Nuno Costa", "biromiro");
    EXPECT_EQ(viewerManager.has("biromiro"),true);
    EXPECT_EQ(viewerManager.has(viewer1),true);
    viewerManager.remove(viewer1);
    EXPECT_EQ(viewerManager.has("biromiro"),false);
    EXPECT_EQ(viewerManager.has(viewer1),false);
}

TEST(viewer_manager, get){
    std::shared_ptr<UserManager> userManager =  std::make_shared<UserManager>();
    ViewerManager viewerManager = ViewerManager(userManager);
    Date birthDate("2001/10/20");
    auto viewer1 = viewerManager.build(birthDate, "Nuno Costa", "biromiro");
    EXPECT_EQ(viewerManager.get("biromiro"),viewer1);
    EXPECT_EQ(viewerManager.get("kekw"),nullptr);
}