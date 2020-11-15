//
// Created by nrtc on 14/11/2020.
//

#ifndef PROJECT_UI_MANAGER_H
#define PROJECT_UI_MANAGER_H

#include "../utils/otherFunctions/auxiliaryFunctions.h"
#include "../model/streamZ/streamZ.h"
#include "../auth/currentSession.h"
#include "ui.h"

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

    const StreamZ &getPlatform() const;

    const CurrentSession &getCurrentSession() const;

    UI *getCurrentUi() const;

    void run() const;

    void setCurrent(UI* ui);
private:
    StreamZ platform;
    CurrentSession currentSession;
    UI* currentUI = nullptr;
};

#endif //PROJECT_UI_MANAGER_H
