//
// Created by nrtc on 14/11/2020.
//

#ifndef PROJECT_INITIALPAGE_H
#define PROJECT_INITIALPAGE_H

#include "../ui_manager.h"

class InitialPage : public UI{
public:
    explicit InitialPage(UIManager& uiManager);
    void run() override;
private:
    UIManager& uiManager;
    void pageOutput() const;
};

#endif //PROJECT_INITIALPAGE_H
