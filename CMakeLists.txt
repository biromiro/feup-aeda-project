cmake_minimum_required(VERSION 3.17)
project(project)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(../libs/googletest)
include_directories(../libs/googletest/googletest/include)
include_directories(../libs/googletest/googlemock/include)

add_executable(project
        main.cpp
        streamZ/streamZ.h
        user/user.h user/user.cpp
        stream/stream.h stream/stream.cpp
        user/Viewer/viewer.h user/Viewer/viewer.cpp
        user/Streamer/streamer.h user/Streamer/streamer.cpp
        user/Admin/admin.h user/Admin/admin.cpp)

target_link_libraries(project gtest gtest_main)