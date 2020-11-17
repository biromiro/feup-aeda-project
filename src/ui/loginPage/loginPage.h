//
// Created by biromiro on 15/11/20.
//

#ifndef PROJECT_LOGINPAGE_H
#define PROJECT_LOGINPAGE_H

#include "../ui_manager.h"
#include "../initialPage/initialPage.h"
#include "../viewerView/viewerView.h"
#include "../streamerView/streamerView.h"
#include "../adminView/adminView.h"

class LoginPage : public UI{
public:
    explicit LoginPage(UIManager& uiManager);
    void run() override;
private:
    UIManager& uiManager;
    void pageOutput() const;
};

#endif //PROJECT_LOGINPAGE_H
