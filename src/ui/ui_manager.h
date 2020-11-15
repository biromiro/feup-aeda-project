//
// Created by nrtc on 14/11/2020.
//

#ifndef PROJECT_UI_MANAGER_H
#define PROJECT_UI_MANAGER_H

#include "../model/streamZ/streamZ.h"
#include "../auth/currentSession.h"

enum class CurrentView{
    INITIAL_PAGE,
    LOGIN_PAGE,
    REGISTER_PAGE,
    STREAMER_VIEW,
    VIEWER_VIEW,
    ADMIN_VIEW,
    LEADERBOARD_VIEW
};

class UIManager{
public:
    UIManager();
    void run();
private:
    StreamZ platform;
    CurrentSession currentSession;
};

#endif //PROJECT_UI_MANAGER_H
