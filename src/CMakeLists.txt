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
        utils/otherFunctions/auxiliaryFunctions.h
        utils/otherFunctions/auxiliaryFunctions.cpp
        ui/ui.h
        ui/ui_manager.h ui/ui_manager.cpp
        ui/adminView/adminView.h ui/adminView/adminView.cpp
        ui/initialPage/initialPage.h ui/initialPage/initialPage.cpp
        ui/leaderboardPage/leaderboardPage.h ui/leaderboardPage/leaderboardPage.cpp
        ui/loginPage/loginPage.h ui/loginPage/loginPage.cpp
        ui/registerPage/registerPage.h ui/registerPage/registerPage.cpp
        ui/streamerView/streamerView.h ui/streamerView/streamerView.cpp
        ui/viewerView/viewerView.h ui/viewerView/viewerView.cpp
        ui/streamView/streamView.h ui/streamView/streamView.cpp
        auth/currentSession.h auth/currentSession.cpp
        exception/invalidAge/invalidAge.h exception/invalidAge/invalidAge.cpp
        exception/invalidFeedback/invalidFeedback.cpp exception/invalidFeedback/invalidFeedback.h
        exception/nicknameNotFound/nicknameNotFound.cpp exception/nicknameNotFound/nicknameNotFound.h
        exception/nicknameAlreadyAdded/nicknameAlreadyAdded.cpp exception/nicknameAlreadyAdded/nicknameAlreadyAdded.h
        exception/streamNotFound/streamNotFound.cpp exception/streamNotFound/streamNotFound.h
        exception/noStreamWithID/noStreamWithID.cpp exception/noStreamWithID/noStreamWithID.h
        exception/invalidStreamAdd/invalidStreamToAdd.cpp exception/invalidStreamAdd/invalidStreamToAdd.h
        exception/streamAlreadyFinished/streamAlreadyFinished.cpp exception/streamAlreadyFinished/streamAlreadyFinished.h
        exception/streamerAlreadyStreaming/streamerAlreadyStreaming.cpp exception/streamerAlreadyStreaming/streamerAlreadyStreaming.h
        exception/invalidStreamBuild/invalidStreamBuild.cpp exception/invalidStreamBuild/invalidStreamBuild.h
        exception/userAlreadyExists/userAlreadyExists.cpp exception/userAlreadyExists/userAlreadyExists.h
        exception/userNotFound/userNotFound.cpp exception/userNotFound/userNotFound.h
        exception/adminAlreadySet/adminAlreadySet.cpp exception/adminAlreadySet/adminAlreadySet.h
        exception/adminNotSet/adminNotSet.cpp exception/adminNotSet/adminNotSet.h
        model/streamZ/streamZ.h
        model/user/user.h model/user/user.cpp
        model/user/user_manager.h model/user/user_manager.cpp
        model/stream/stream.h model/stream/stream.cpp
        model/stream/streamManager.h model/stream/streamManager.cpp
        model/user/viewer/viewer.h model/user/viewer/viewer.cpp
        model/user/viewer/viewer_manager.h model/user/viewer/viewer_manager.cpp
        model/user/streamer/streamer.h model/user/streamer/streamer.cpp
        model/user/streamer/streamer_manager.h model/user/streamer/streamer_manager.cpp
        model/user/admin/admin.h model/user/admin/admin.cpp
        model/user/admin/admin_manager.h model/user/admin/admin_manager.cpp
        utils/date/date.h utils/date/date.cpp model/stream/privateStream/privateStream.h
        model/stream/privateStream/privateStream.cpp model/stream/publicStream/publicStream.h
        model/stream/publicStream/publicStream.cpp model/streamZ/streamZ.cpp
        utils/leaderboard/leaderboard.h
        utils/leaderboard/leaderboard_manager.h
        utils/leaderboard/leaderboard_manager.cpp
        model/stream/finishedStream/finishedStream.cpp model/stream/finishedStream/finishedStream.h)


add_executable(application
        main.cpp
        utils/otherFunctions/auxiliaryFunctions.h
        utils/otherFunctions/auxiliaryFunctions.cpp
        ui/ui.h
        ui/ui_manager.h ui/ui_manager.cpp
        ui/adminView/adminView.h ui/adminView/adminView.cpp
        ui/initialPage/initialPage.h ui/initialPage/initialPage.cpp
        ui/leaderboardPage/leaderboardPage.h ui/leaderboardPage/leaderboardPage.cpp
        ui/loginPage/loginPage.h ui/loginPage/loginPage.cpp
        ui/registerPage/registerPage.h ui/registerPage/registerPage.cpp
        ui/streamerView/streamerView.h ui/streamerView/streamerView.cpp
        ui/viewerView/viewerView.h ui/viewerView/viewerView.cpp
        ui/streamView/streamView.h ui/streamView/streamView.cpp
        auth/currentSession.h auth/currentSession.cpp
        exception/invalidAge/invalidAge.h exception/invalidAge/invalidAge.cpp
        model/streamZ/streamZ.h
        model/user/user.h model/user/user.cpp
        model/user/user_manager.h model/user/user_manager.cpp
        model/stream/stream.h model/stream/stream.cpp
        model/stream/streamManager.h model/stream/streamManager.cpp
        model/user/viewer/viewer.h model/user/viewer/viewer.cpp
        model/user/viewer/viewer_manager.h model/user/viewer/viewer_manager.cpp
        model/user/streamer/streamer.h model/user/streamer/streamer.cpp
        model/user/streamer/streamer_manager.h model/user/streamer/streamer_manager.cpp
        model/user/admin/admin.h model/user/admin/admin.cpp
        model/user/admin/admin_manager.h model/user/admin/admin_manager.cpp
        utils/date/date.h utils/date/date.cpp model/stream/privateStream/privateStream.h
        model/stream/privateStream/privateStream.cpp model/stream/publicStream/publicStream.h
        model/stream/publicStream/publicStream.cpp model/streamZ/streamZ.cpp
        utils/leaderboard/leaderboard.h
        utils/leaderboard/leaderboard_manager.h
        utils/leaderboard/leaderboard_manager.cpp
        model/stream/finishedStream/finishedStream.cpp model/stream/finishedStream/finishedStream.h
        exception/invalidFeedback/invalidFeedback.cpp exception/invalidFeedback/invalidFeedback.h
        exception/nicknameNotFound/nicknameNotFound.cpp exception/nicknameNotFound/nicknameNotFound.h
        exception/nicknameAlreadyAdded/nicknameAlreadyAdded.cpp exception/nicknameAlreadyAdded/nicknameAlreadyAdded.h
        exception/streamNotFound/streamNotFound.cpp exception/streamNotFound/streamNotFound.h
        exception/noStreamWithID/noStreamWithID.cpp exception/noStreamWithID/noStreamWithID.h
        exception/invalidStreamAdd/invalidStreamToAdd.cpp exception/invalidStreamAdd/invalidStreamToAdd.h
        exception/streamAlreadyFinished/streamAlreadyFinished.cpp exception/streamAlreadyFinished/streamAlreadyFinished.h
        exception/streamerAlreadyStreaming/streamerAlreadyStreaming.cpp exception/streamerAlreadyStreaming/streamerAlreadyStreaming.h
        exception/invalidStreamBuild/invalidStreamBuild.cpp exception/invalidStreamBuild/invalidStreamBuild.h exception/userAlreadyExists/userAlreadyExists.cpp exception/userAlreadyExists/userAlreadyExists.h exception/userNotFound/userNotFound.cpp exception/userNotFound/userNotFound.h exception/adminAlreadySet/adminAlreadySet.cpp exception/adminAlreadySet/adminAlreadySet.h exception/adminNotSet/adminNotSet.cpp exception/adminNotSet/adminNotSet.h)


target_include_directories(project PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(project PUBLIC gtest_main coverage_config)