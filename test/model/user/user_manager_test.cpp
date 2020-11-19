//
// Created by biromiro on 29/10/20.
//

#include <gtest/gtest.h>
#include <model/user/user_manager.h>
#include <model/user/viewer/viewer.h>
#include <model/user/streamer/streamer.h>
#include <model/user/admin/admin.h>
#include <exception/userAlreadyExists/userAlreadyExists.h>
#include <exception/userNotFound/userNotFound.h>

using testing::Eq;


TEST(user_manager, add){
    UserManager userManager;
    Date birthDate("2001/10/20");
    auto viewer = std::make_shared<Viewer>(birthDate,"André Moreira","Dustini", "dkajniksda");
    auto viewer2 = std::make_shared<Viewer>(birthDate,"André Pereira","dustibo", "knadsjkdna");
    auto streamer =  std::make_shared<Streamer>(birthDate, "Nuno Costa", "biromiro", "aknsdbnasd");
    auto admin = std::make_shared<Admin>(birthDate, "Úrsula Maior", "urmaior", "aisdhdiouasd");
    EXPECT_EQ(userManager.add(std::dynamic_pointer_cast<User>(viewer)), true);
    EXPECT_EQ(userManager.add(std::dynamic_pointer_cast<User>(streamer)), true);
    EXPECT_THROW(userManager.add(std::dynamic_pointer_cast<User>(viewer)), UserAlreadyExists);
    try{
        userManager.add(std::dynamic_pointer_cast<User>(viewer));
    }
    catch(UserAlreadyExists &uae){
        EXPECT_EQ(uae.getMessage(),"The user you're trying to add already exists!");
    }
    EXPECT_EQ(userManager.add(std::dynamic_pointer_cast<User>(viewer2)), true);
    EXPECT_EQ(userManager.add(std::dynamic_pointer_cast<User>(admin)), true);
    EXPECT_THROW(userManager.add(std::dynamic_pointer_cast<User>(admin)), UserAlreadyExists);
    try{
        userManager.add(std::dynamic_pointer_cast<User>(admin));
    }
    catch(UserAlreadyExists &uae2){
        EXPECT_EQ(uae2.getMessage(),"The user you're trying to add already exists!");
    }
    EXPECT_EQ(userManager.getUsers().size(),4);
}

TEST(user_manager, remove){
    UserManager userManager;
    Date birthDate("2001/10/20");
    auto viewer = std::make_shared<Viewer>(birthDate,"André Moreira","Dustini", "dkajniksda");
    auto viewer2 = std::make_shared<Viewer>(birthDate,"André Pereira","dustibo", "knadsjkdna");
    auto streamer =  std::make_shared<Streamer>(birthDate, "Nuno Costa", "biromiro", "aknsdbnasd");
    auto admin = std::make_shared<Admin>(birthDate, "Úrsula Maior", "urmaior", "aisdhdiouasd");
    userManager.add(std::dynamic_pointer_cast<User>(viewer));
    userManager.add(std::dynamic_pointer_cast<User>(viewer2));
    EXPECT_EQ(userManager.getUsers().size(),2);
    EXPECT_THROW(userManager.remove(std::dynamic_pointer_cast<User>(streamer)),UserNotFound);
    try{
        userManager.remove(std::dynamic_pointer_cast<User>(streamer));
    }
    catch (UserNotFound &unt) {
        EXPECT_EQ(unt.getMessage(),"The user you're looking for does not exist!");
    }
    EXPECT_EQ(userManager.remove(std::dynamic_pointer_cast<User>(viewer)), true);
    userManager.add(std::dynamic_pointer_cast<User>(admin));
    EXPECT_EQ(userManager.remove(std::dynamic_pointer_cast<User>(admin)), true);
    EXPECT_EQ(userManager.getUsers().size(),1);
}

TEST(user_manager, has){
    UserManager userManager;
    Date birthDate("2001/10/20");
    auto viewer = std::make_shared<Viewer>(birthDate,"André Moreira","Dustini", "dkajniksda");
    auto viewer2 = std::make_shared<Viewer>(birthDate,"André Pereira","dustibo", "knadsjkdna");
    auto streamer =  std::make_shared<Streamer>(birthDate, "Nuno Costa", "biromiro", "aknsdbnasd");
    auto admin = std::make_shared<Admin>(birthDate, "Úrsula Maior", "urmaior", "aisdhdiouasd");
    userManager.add(std::dynamic_pointer_cast<User>(viewer));
    userManager.add(std::dynamic_pointer_cast<User>(viewer2));
    EXPECT_EQ(userManager.has(std::dynamic_pointer_cast<User>(streamer)), false);
    EXPECT_EQ(userManager.has("biromiro"), false);
    EXPECT_EQ(userManager.has(std::dynamic_pointer_cast<User>(viewer)), true);
    EXPECT_EQ(userManager.has("Dustini"), true);
    userManager.add(std::dynamic_pointer_cast<User>(admin));
    EXPECT_EQ(userManager.has(std::dynamic_pointer_cast<User>(admin)), true);
    userManager.remove(std::dynamic_pointer_cast<User>(admin));
    EXPECT_EQ(userManager.has("urmaior"), false);
}

TEST(user_manager, getters){
    UserManager userManager;
    Date birthDate("2001/10/20");
    auto viewer = std::make_shared<Viewer>(birthDate,"André Moreira","Dustini", "dkajniksda");
    auto viewer2 = std::make_shared<Viewer>(birthDate,"André Pereira","dustibo", "knadsjkdna");
    auto streamer =  std::make_shared<Streamer>(birthDate, "Nuno Costa", "biromiro", "aknsdbnasd");
    auto admin = std::make_shared<Admin>(birthDate, "Úrsula Maior", "urmaior", "aisdhdiouasd");
    userManager.add(std::dynamic_pointer_cast<User>(viewer));
    userManager.add(std::dynamic_pointer_cast<User>(viewer2));
    userManager.add(std::dynamic_pointer_cast<User>(admin));
    EXPECT_EQ(userManager.get("urmaior"), std::dynamic_pointer_cast<User>(admin));
    EXPECT_EQ(userManager.getUsers().size(),3);
    userManager.remove(std::dynamic_pointer_cast<User>(admin));
    EXPECT_EQ(userManager.get("urmaior"), nullptr);
    EXPECT_EQ(userManager.getUsers().size(),2);
    EXPECT_EQ(*(userManager.getUsers().find(viewer)), viewer);
    EXPECT_EQ(userManager.getUsers().find(streamer), userManager.getUsers().end());
}
