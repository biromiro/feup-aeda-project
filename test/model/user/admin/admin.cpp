//
// Created by biromiro on 01/11/20.
//


#include <gtest/gtest.h>
#include <model/user/admin/admin.h>

using testing::Eq;


TEST(admin,constructor){
    Date birthDate(2001,5,16);
    Admin admin1(birthDate, "Miguel", "CEOdebottomtext", "muitotriste");
    EXPECT_EQ(admin1.getUserType(), UserTypes::ADMIN);
}

