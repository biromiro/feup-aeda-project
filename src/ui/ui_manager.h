//
// Created by nrtc on 14/11/2020.
//

#ifndef PROJECT_UI_MANAGER_H
#define PROJECT_UI_MANAGER_H

#include "../utils/otherFunctions/auxiliaryFunctions.h"
#include "../model/streamZ/streamZ.h"
#include "../auth/currentSession.h"
#include "ui.h"

class UIManager{
public:
    UIManager(StreamZ& platform, CurrentSession& currentSession);

    [[nodiscard]] StreamZ &getPlatform() const;

    [[nodiscard]] CurrentSession &getCurrentSession() const;

    void run() const;

    void setCurrent(UI* ui);
private:
    StreamZ& platform;
    CurrentSession& currentSession;
    UI* currentUI = nullptr;
};

#endif //PROJECT_UI_MANAGER_H
