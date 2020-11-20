//
// Created by nrtc on 14/11/2020.
//

#include "initialPage.h"


InitialPage::InitialPage(UIManager& uiManager) : uiManager(uiManager) {}

void InitialPage::run() {
    char answer;
    do{
        pageOutput();
        std::cout << HIDE_CURSOR;
        answer = _getch_();
        switch (answer) {
            case '1':
                uiManager.setCurrent(new LoginPage(uiManager));
                uiManager.run();
                break;
            case '2':
                uiManager.setCurrent(new RegisterPage(uiManager));
                uiManager.run();
                break;
            case '0':
                uiManager.getPlatform().finish();
                break;
            default:
                break;
        }
        std::cout << CLEAR_SCREEN << GO_TO_TOP << SHOW_CURSOR;
    }while(answer != '0');
}

void InitialPage::pageOutput() {
    std::cout << "***** Welcome to StreamZ! *****" << std::endl;
    std::cout << "\n\t1 - Login" << std::endl;
    std::cout << "\t2 - Register" << std::endl;
    std::cout << "\t0 - Exit" << std::endl;
    std::cout << "\n********************************" << std::endl;
}

