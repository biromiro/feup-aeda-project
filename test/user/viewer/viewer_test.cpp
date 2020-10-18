//
// Created by biromiro on 18/10/20.
//


#include <gtest/gtest.h>
#include <user/viewer/viewer.h>

using testing::Eq;


TEST(viewer, constructor_test){
    Viewer viewer1(18, "Palpa", "Palps");
    EXPECT_EQ(viewer1.getUserType(), UserTypes::VIEWER);
}