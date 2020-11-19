//
// Created by nrtc on 14/11/2020.
//

#ifndef PROJECT_INITIALPAGE_H
#define PROJECT_INITIALPAGE_H

#include "../ui_manager.h"
#include "../loginPage/loginPage.h"
#include "../registerPage/registerPage.h"

class InitialPage : public UI{
public:
    explicit InitialPage(UIManager& uiManager);
    void run() override;
private:
    UIManager& uiManager;
    static void pageOutput() ;
};

#endif //PROJECT_INITIALPAGE_H
