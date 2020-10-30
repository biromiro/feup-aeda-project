//
// Created by biromiro on 29/10/20.
//

#include <gtest/gtest.h>
#include <user/user_manager.h>
#include <user/viewer/viewer.h>
#include <user/streamer/streamer.h>
#include <user/admin/admin.h>

using testing::Eq;


TEST(user_manager, add_method){
    UserManager userManager;
    Date birthDate("2001/10/20");
    Viewer viewer(birthDate,"André Moreira","Dustini");
    Viewer viewer2(birthDate,"André Pereira","dustibo");
    Streamer streamer(birthDate, "Nuno Costa", "biromiro");
    Admin admin(birthDate, "Úrsula Maior", "urmaior");
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&viewer)), true);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&streamer)), true);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&viewer)), false);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&viewer)), false);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&admin)), true);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&admin)), false);
}

TEST(user_manager, remove_method) {
    UserManager userManager;
    Date birthDate("2001/10/20");
    Viewer viewer(birthDate,"André Moreira","Dustini");
    Viewer viewer2(birthDate,"André Pereira","dustibo");
    Streamer streamer(birthDate, "Nuno Costa", "biromiro");
    Admin admin(birthDate, "Úrsula Maior", "urmaior");
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&viewer)), true);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&streamer)), true);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&viewer)), false);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&viewer)), false);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&admin)), true);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&admin)), false);
    EXPECT_EQ(userManager.remove(dynamic_cast<User*>(&streamer)), true);
    EXPECT_EQ(userManager.remove(dynamic_cast<User*>(&viewer2)), false);
}

TEST(user_manager, has_method) {
    UserManager userManager;
    Date birthDate("2001/10/20");
    Viewer viewer(birthDate,"André Moreira","Dustini");
    Viewer viewer2(birthDate,"André Pereira","dustibo");
    Streamer streamer(birthDate, "Nuno Costa", "biromiro");
    Admin admin(birthDate, "Úrsula Maior", "urmaior");
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&viewer)), true);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&streamer)), true);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&viewer)), false);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&viewer)), false);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&admin)), true);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&admin)), false);
    EXPECT_EQ(userManager.has(dynamic_cast<User*>(&streamer)), true);
    EXPECT_EQ(userManager.has(dynamic_cast<User*>(&viewer2)), false);
    EXPECT_EQ(userManager.has(dynamic_cast<User*>(&streamer)), true);
}

TEST(user_manager, has_by_nickname_method) {
    UserManager userManager;
    Date birthDate("2001/10/20");
    Viewer viewer(birthDate,"André Moreira","Dustini");
    Viewer viewer2(birthDate,"André Pereira","dustibo");
    Streamer streamer(birthDate, "Nuno Costa", "biromiro");
    Admin admin(birthDate, "Úrsula Maior", "urmaior");
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&viewer)), true);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&streamer)), true);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&viewer)), false);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&viewer)), false);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&admin)), true);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&admin)), false);
    EXPECT_EQ(userManager.has(streamer.getNickname()), true);
    EXPECT_EQ(userManager.has(viewer2.getNickname()), false);
    EXPECT_EQ(userManager.has(viewer.getNickname()), true);
    EXPECT_EQ(userManager.has(streamer.getNickname()), true);
}

TEST(user_manager, get_by_nickname_method) {
    UserManager userManager;
    Date birthDate("2001/10/20");
    Viewer viewer(birthDate,"André Moreira","Dustini");
    Viewer viewer2(birthDate,"André Pereira","dustibo");
    Streamer streamer(birthDate, "Nuno Costa", "biromiro");
    Admin admin(birthDate, "Úrsula Maior", "urmaior");
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&viewer)), true);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&streamer)), true);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&viewer)), false);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&viewer)), false);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&admin)), true);
    EXPECT_EQ(userManager.add(dynamic_cast<User*>(&admin)), false);
    EXPECT_EQ(userManager.get(streamer.getNickname()), dynamic_cast<User*>(&streamer));
    EXPECT_EQ(userManager.get(viewer.getNickname()), dynamic_cast<User*>(&viewer));
}


