//
// Created by biromiro on 29/10/20.
//

#include <gtest/gtest.h>
#include <model/user/viewer/viewer.h>
#include <model/user/streamer/streamer.h>
#include <model/user/admin/admin.h>

using testing::Eq;


TEST(user, get_age){
    Date birthDate1("2001/10/20"), birthDate2("2007/10/29"), birthDate3(1969,11,16);
    Viewer viewer(birthDate2,"André Moreira","Dustini", "tenso");
    Streamer streamer(birthDate1, "Nuno Costa", "biromiro", "olaoscra");
    Admin admin(birthDate3, "Úrsula Maior", "urmaior", "kekw120");
    EXPECT_EQ(viewer.getAge(), 13);
    EXPECT_EQ(streamer.getAge(), 19);
    EXPECT_EQ(admin.getAge(), 51);
}

TEST(user, get_name){
    Date birthDate1("2001/10/20"), birthDate2("2007/10/29"), birthDate3(1969,11,16);
    Viewer viewer(birthDate2,"André Moreira","Dustini", "tenso");
    Streamer streamer(birthDate1, "Nuno Costa", "biromiro", "olaoscra");
    Admin admin(birthDate3, "Úrsula Maior", "urmaior", "kekw120");
    EXPECT_EQ(viewer.getName(), "André Moreira");
    EXPECT_EQ(streamer.getName(), "Nuno Costa");
    EXPECT_EQ(admin.getName(), "Úrsula Maior");
}

TEST(user, get_nickname){
    Date birthDate1("2001/10/20"), birthDate2("2007/10/29"), birthDate3(1969,11,16);
    Viewer viewer(birthDate2,"André Moreira","Dustini", "tenso");
    Streamer streamer(birthDate1, "Nuno Costa", "biromiro", "olaoscra");
    Admin admin(birthDate3, "Úrsula Maior", "urmaior", "kekw120");
    EXPECT_EQ(viewer.getNickname(), "Dustini");
    EXPECT_EQ(streamer.getNickname(), "biromiro");
    EXPECT_EQ(admin.getNickname(), "urmaior");
}

TEST(user, get_birthdate){
    Date birthDate1("2001/10/20"), birthDate2("2007/10/29"), birthDate3(1969,11,16);
    Viewer viewer(birthDate2,"André Moreira","Dustini", "tenso");
    Streamer streamer(birthDate1, "Nuno Costa", "biromiro", "olaoscra");
    Admin admin(birthDate3, "Úrsula Maior", "urmaior", "kekw120");
    EXPECT_EQ(viewer.getBirthDate(), birthDate2);
    EXPECT_EQ(streamer.getBirthDate(), birthDate1);
    EXPECT_EQ(admin.getBirthDate(), birthDate3);
}

TEST(user, update_birthdate){
    Date birthDate1("2001/10/20"), birthDate2("2007/10/29"), birthDate3(1969,11,16);
    Viewer viewer(birthDate2,"André Moreira","Dustini", "tenso");
    Streamer streamer(birthDate1, "Nuno Costa", "biromiro", "olaoscra");
    EXPECT_EQ(viewer.getBirthDate(), birthDate2);
    viewer.updateBirthDate(birthDate3);
    EXPECT_EQ(viewer.getBirthDate(),birthDate3);
    EXPECT_EQ(streamer.getBirthDate(), birthDate1);
    streamer.updateBirthDate(birthDate3);
    EXPECT_EQ(streamer.getBirthDate(), birthDate3);
}

TEST(user, update_name){
    Date birthDate1("2001/10/20"), birthDate2("2007/10/29"), birthDate3(1969,11,16);
    Viewer viewer(birthDate2,"André Moreira","Dustini", "tenso");
    Streamer streamer(birthDate1, "Nuno Costa", "biromiro", "olaoscra");
    EXPECT_EQ(viewer.getName(), "André Moreira");
    viewer.updateName("Nuno Costa");
    EXPECT_EQ(viewer.getName(), "Nuno Costa");
    streamer.updateName("Muito Estranho");
    EXPECT_EQ(streamer.getName(), "Muito Estranho");
}

TEST(user, update_nickname){
    Date birthDate1("2001/10/20"), birthDate2("2007/10/29"), birthDate3(1969,11,16);
    Viewer viewer(birthDate2,"André Moreira","Dustini", "tenso");
    Streamer streamer(birthDate1, "Nuno Costa", "biromiro", "olaoscra");
    EXPECT_EQ(viewer.getNickname(), "Dustini");
    viewer.updateNickname("Dustini, O Ditador, David Luís");
    EXPECT_EQ(viewer.getNickname(), "Dustini, O Ditador, David Luís");
    streamer.updateNickname("kekw");
    EXPECT_EQ(streamer.getNickname(), "kekw");
}
