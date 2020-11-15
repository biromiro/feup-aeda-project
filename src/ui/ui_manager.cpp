//
// Created by nrtc on 14/11/2020.
//

#include "ui_manager.h"

UIManager::UIManager(){
    platform = StreamZ();
    platform.initialize();
    currentSession = CurrentSession(platform.getUserManager());
}

void UIManager::run() const{
    currentUI->run();
}

void UIManager::setCurrent(UI *ui) {
    currentUI = ui;
}

const StreamZ &UIManager::getPlatform() const {
    return platform;
}

const CurrentSession &UIManager::getCurrentSession() const {
    return currentSession;
}

UI *UIManager::getCurrentUi() const {
    return currentUI;
}

