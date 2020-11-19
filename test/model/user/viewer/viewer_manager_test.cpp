//
// Created by biromiro on 01/11/20.
//

#include <gtest/gtest.h>
#include <model/user/viewer/viewer_manager.h>
#include <exception/nicknameAlreadyAdded/nicknameAlreadyAdded.h>
#include <exception/userAlreadyExists/userAlreadyExists.h>
#include <exception/userNotFound/userNotFound.h>

using testing::Eq;


TEST(viewer_manager, build_add){
    std::shared_ptr<UserManager> userManager =  std::make_shared<UserManager>();
    ViewerManager viewerManager = ViewerManager(userManager);
    Date birthDate("2001/10/20");
    EXPECT_EQ(viewerManager.getViewers().size(), 0);
    EXPECT_EQ(viewerManager.build(birthDate, "Nuno Costa", "biromiro", "hehe") != nullptr, true);
    EXPECT_EQ(viewerManager.getViewers().size(), 1);
    EXPECT_THROW(viewerManager.build(birthDate, "Pedro Costa", "biromiro", "mekiepessoal"), NicknameAlreadyAdded);
    try{
        viewerManager.build(birthDate, "Pedro Costa", "biromiro", "mekiepessoal");
    }
    catch(NicknameAlreadyAdded &naa){
        EXPECT_EQ(naa.getMessage(),"Nickname already in use by another user!");
    }
}

TEST(viewer_manager, remove){
    std::shared_ptr<UserManager> userManager =  std::make_shared<UserManager>();
    ViewerManager viewerManager = ViewerManager(userManager);
    Date birthDate("2001/10/20");
    EXPECT_EQ(viewerManager.getViewers().size(), 0);
    auto viewer1 = viewerManager.build(birthDate, "Nuno Costa", "biromiro", "olakekwk");
    EXPECT_EQ(viewerManager.getViewers().size(), 1);
    EXPECT_EQ(viewerManager.remove(viewer1), true);
    EXPECT_THROW(viewerManager.remove(viewer1), UserNotFound);
    try{
        viewerManager.remove(viewer1);
    }
    catch (UserNotFound & unt) {
        EXPECT_EQ(unt.getMessage(),"The viewer you're trying to remove does not exist!");
    }
    EXPECT_EQ(viewerManager.getViewers().size(), 0);
}

TEST(viewer_manager, has){
    std::shared_ptr<UserManager> userManager =  std::make_shared<UserManager>();
    ViewerManager viewerManager = ViewerManager(userManager);
    Date birthDate("2001/10/20");
    EXPECT_EQ(viewerManager.has("biromiro"),false);
    auto viewer1 = viewerManager.build(birthDate, "Nuno Costa", "biromiro", "olakekwk");
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
    auto viewer1 = viewerManager.build(birthDate, "Nuno Costa", "biromiro", "olakekkw");
    EXPECT_EQ(viewerManager.get("biromiro"),viewer1);
    EXPECT_EQ(viewerManager.get("kekw"),nullptr);
}