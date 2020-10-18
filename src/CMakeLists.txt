cmake_minimum_required(VERSION 3.17)
project(project)

set(CMAKE_CXX_STANDARD 14)

add_executable(project
        main.cpp
        streamZ/streamZ.h
        user/user.h user/user.cpp
        stream/stream.h stream/stream.cpp
        user/viewer/viewer.h user/viewer/viewer.cpp
        user/streamer/streamer.h user/streamer/streamer.cpp
        user/admin/admin.h user/admin/admin.cpp
        utils/date/date.h utils/date/date.cpp stream/privateStream/privateStream.h stream/privateStream/privateStream.cpp stream/publicStream/publicStream.h stream/publicStream/publicStream.cpp user/viewer/viewer.h)
