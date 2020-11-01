//
// Created by biromiro on 29/10/20.
//

#include <gtest/gtest.h>
#include <user/user_manager.h>
#include <user/viewer/viewer.h>
#include <user/streamer/streamer.h>
#include <user/admin/admin.h>

using testing::Eq;


TEST(user_manager, add){
    UserManager userManager;
    Date birthDate("2001/10/20");
    auto viewer = std::make_shared<Viewer>(birthDate,"André Moreira","Dustini");
    auto viewer2 = std::make_shared<Viewer>(birthDate,"André Pereira","dustibo");
    auto streamer =  std::make_shared<Streamer>(birthDate, "Nuno Costa", "biromiro");
    auto admin = std::make_shared<Admin>(birthDate, "Úrsula Maior", "urmaior");
    EXPECT_EQ(userManager.add(std::dynamic_pointer_cast<User>(viewer)), true);
    EXPECT_EQ(userManager.add(std::dynamic_pointer_cast<User>(streamer)), true);
    EXPECT_EQ(userManager.add(std::dynamic_pointer_cast<User>(viewer)), false);
    EXPECT_EQ(userManager.add(std::dynamic_pointer_cast<User>(viewer2)), true);
    EXPECT_EQ(userManager.add(std::dynamic_pointer_cast<User>(admin)), true);
    EXPECT_EQ(userManager.add(std::dynamic_pointer_cast<User>(admin)), false);
    EXPECT_EQ(userManager.getUsers().size(),4);
}

TEST(user_manager, remove){
    UserManager userManager;
    Date birthDate("2001/10/20");
    auto viewer = std::make_shared<Viewer>(birthDate,"André Moreira","Dustini");
    auto viewer2 = std::make_shared<Viewer>(birthDate,"André Pereira","dustibo");
    auto streamer =  std::make_shared<Streamer>(birthDate, "Nuno Costa", "biromiro");
    auto admin = std::make_shared<Admin>(birthDate, "Úrsula Maior", "urmaior");
    userManager.add(std::dynamic_pointer_cast<User>(viewer));
    userManager.add(std::dynamic_pointer_cast<User>(viewer2));
    EXPECT_EQ(userManager.getUsers().size(),2);
    EXPECT_EQ(userManager.remove(std::dynamic_pointer_cast<User>(streamer)), false);
    EXPECT_EQ(userManager.remove(std::dynamic_pointer_cast<User>(viewer)), true);
    userManager.add(std::dynamic_pointer_cast<User>(admin));
    EXPECT_EQ(userManager.remove(std::dynamic_pointer_cast<User>(admin)), true);
    EXPECT_EQ(userManager.getUsers().size(),1);
}

TEST(user_manager, has){
    UserManager userManager;
    Date birthDate("2001/10/20");
    auto viewer = std::make_shared<Viewer>(birthDate,"André Moreira","Dustini");
    auto viewer2 = std::make_shared<Viewer>(birthDate,"André Pereira","dustibo");
    auto streamer =  std::make_shared<Streamer>(birthDate, "Nuno Costa", "biromiro");
    auto admin = std::make_shared<Admin>(birthDate, "Úrsula Maior", "urmaior");
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
    auto viewer = std::make_shared<Viewer>(birthDate,"André Moreira","Dustini");
    auto viewer2 = std::make_shared<Viewer>(birthDate,"André Pereira","dustibo");
    auto streamer =  std::make_shared<Streamer>(birthDate, "Nuno Costa", "biromiro");
    auto admin = std::make_shared<Admin>(birthDate, "Úrsula Maior", "urmaior");
    userManager.add(std::dynamic_pointer_cast<User>(viewer));
    userManager.add(std::dynamic_pointer_cast<User>(viewer2));
    userManager.add(std::dynamic_pointer_cast<User>(admin));
    EXPECT_EQ(userManager.get("urmaior"), std::dynamic_pointer_cast<User>(admin));
    userManager.remove(std::dynamic_pointer_cast<User>(admin));
    EXPECT_EQ(userManager.get("urmaior"), nullptr);
}


