//
// Created by nrtc on 14/11/2020.
//

#include "ui_manager.h"

UIManager::UIManager(StreamZ& streamZ, CurrentSession& currentSession) : platform(streamZ), currentSession(currentSession) {
    platform.initialize();
}

void UIManager::run() const{
    currentUI->run();
}

void UIManager::setCurrent(UI *ui) {
    currentUI = ui;
}

StreamZ &UIManager::getPlatform() const {
    return platform;
}

CurrentSession &UIManager::getCurrentSession() const {
    return currentSession;
}

