//
// Created by biromiro on 01/11/20.
//

#include <gtest/gtest.h>
#include <model/user/admin/admin_manager.h>


TEST(admin_manager,build_add_remove){
    std::shared_ptr<UserManager> userManager =  std::make_shared<UserManager>();
    AdminManager adminManager = AdminManager(userManager);
    Date birthDate(2001,10,20);
    auto admin2 = std::make_shared<Admin>(birthDate,"vruh momento 2","cao manteiga", "callonmeeeee");
    EXPECT_EQ(adminManager.remove(),false);
    EXPECT_EQ(adminManager.build(birthDate,"Bruh momento", "buttah dog", "tenso"),true);
    EXPECT_EQ(adminManager.add(admin2), false);
    EXPECT_EQ(adminManager.build(birthDate,"bruj momento 3","catal inodoro", "muitotriste"),false);
    EXPECT_EQ(adminManager.remove(),true);
    EXPECT_EQ(adminManager.add(admin2),true);
}

TEST(admin_manager, is_get){
    std::shared_ptr<UserManager> userManager =  std::make_shared<UserManager>();
    AdminManager adminManager = AdminManager(userManager);
    Date birthDate(2001,10,20);
    auto admin = std::make_shared<Admin>(birthDate,"vruh momento","cao manteiga", "ahahaha");
    adminManager.add(admin);
    auto admin2 = std::make_shared<Admin>(birthDate, "vroooooom", "party cat", "kekwahaha");
    EXPECT_EQ(adminManager.is(admin), true);
    EXPECT_EQ(adminManager.is(admin2), false);
    EXPECT_EQ(adminManager.is("cao manteiga"), true);
    EXPECT_EQ(adminManager.is("buttah dog"), false);
    EXPECT_EQ(adminManager.get() == admin, true);
    EXPECT_EQ(adminManager.get() == admin2,false);
}
