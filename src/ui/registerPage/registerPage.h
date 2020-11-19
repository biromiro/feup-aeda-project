//
// Created by biromiro on 15/11/20.
//

#ifndef PROJECT_REGISTERPAGE_H
#define PROJECT_REGISTERPAGE_H

#include "../ui_manager.h"
#include "../initialPage/initialPage.h"

class RegisterPage : public UI{
public:
    explicit RegisterPage(UIManager& uiManager);
    void run() override;
private:
    UIManager& uiManager;
    static void pageOutput() ;
    bool streamerRegister();
    bool viewerRegister();
    void getUserInfo(Date& birthDate, std::string& name, std::string& nickname, std::string& password);
};

#endif //PROJECT_REGISTERPAGE_H
