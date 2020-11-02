# Use C++17
set(CMAKE_CXX_STANDARD 17)
# Require (at least) it
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Don't use e.g. GNU extension (like -std=gnu++11) for portability
set(CMAKE_CXX_EXTENSIONS OFF)

if (WIN32)
    link_libraries(wsock32 ws2_32)
    set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32")
    SET(CMAKE_CXX_FLAGS -Wcpp)
endif (WIN32)


add_library(project
        main.cpp
        streamZ/streamZ.h
        user/user.h user/user.cpp
        user/user_manager.h user/user_manager.cpp
        stream/stream.h stream/stream.cpp
        user/viewer/viewer.h user/viewer/viewer.cpp
        user/viewer/viewer_manager.h user/viewer/viewer_manager.cpp
        user/streamer/streamer.h user/streamer/streamer.cpp
        user/streamer/streamer_manager.h user/streamer/streamer_manager.cpp
        user/admin/admin.h user/admin/admin.cpp
        user/admin/admin_manager.h user/admin/admin_manager.cpp
        utils/date/date.h utils/date/date.cpp stream/privateStream/privateStream.h
        stream/privateStream/privateStream.cpp stream/publicStream/publicStream.h
        stream/publicStream/publicStream.cpp streamZ/streamZ.cpp
        utils/leaderboard/leaderboard.h
        utils/leaderboard/leaderboard_manager.h
        utils/leaderboard/leaderboard_manager.cpp
        stream/streamManager.cpp stream/streamManager.h stream/finishedStream/finishedStream.cpp stream/finishedStream/finishedStream.h)


add_executable(application
        main.cpp
        streamZ/streamZ.h
        user/user.h user/user.cpp
        user/user_manager.h user/user_manager.cpp
        stream/stream.h stream/stream.cpp
        user/viewer/viewer.h user/viewer/viewer.cpp
        user/viewer/viewer_manager.h user/viewer/viewer_manager.cpp
        user/streamer/streamer.h user/streamer/streamer.cpp
        user/streamer/streamer_manager.h user/streamer/streamer_manager.cpp
        user/admin/admin.h user/admin/admin.cpp
        user/admin/admin_manager.h user/admin/admin_manager.cpp
        utils/date/date.h utils/date/date.cpp stream/privateStream/privateStream.h
        stream/privateStream/privateStream.cpp stream/publicStream/publicStream.h
        stream/publicStream/publicStream.cpp streamZ/streamZ.cpp
        utils/leaderboard/leaderboard.h
        utils/leaderboard/leaderboard_manager.h
        utils/leaderboard/leaderboard_manager.cpp
        stream/streamManager.cpp stream/streamManager.h stream/finishedStream/finishedStream.cpp stream/finishedStream/finishedStream.h)


target_include_directories(project PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(project PUBLIC gtest_main coverage_config)