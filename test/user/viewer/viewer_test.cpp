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

TEST(viewer, constructor_test_invalid_age){
    EXPECT_THROW(Viewer* a = new Viewer(11, "Palpa", "Palps"), std::invalid_argument);
    try{
        Viewer* a = new Viewer(11, "Palpa", "Palps");
    }
    catch (const std::invalid_argument &ia) {
        //EXPECT_EQ(ia.what(), "Minimum Age Not Met");
    }
}