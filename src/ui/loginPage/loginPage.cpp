//
// Created by biromiro on 15/11/20.
//

#include "loginPage.h"



LoginPage::LoginPage(UIManager &uiManager) : uiManager(uiManager){}

void LoginPage::run() {
    char answer = ' ';
    bool started = false;
    std::string nickname, password;
    do{
        if(started) answer = getch();
        std::cout << CLEAR_SCREEN << GO_TO_TOP << SHOW_CURSOR;
        pageOutput();
        if(answer != *ESC) {
            std::cout << "Nickname: ";
            getlineCIN(nickname);
            std::cout << "Password: ";
            getlineCIN(password);
            if (uiManager.getCurrentSession().login(nickname, password)){
                std::cout << CLEAR_SCREEN << GO_TO_TOP << HIDE_CURSOR;
                switch (uiManager.getCurrentSession().getCurrentUser()->getUserType()) {
                    case UserTypes::STREAMER:
                        uiManager.setCurrent(new StreamerView(uiManager));
                        uiManager.run();
                        break;
                    case UserTypes::VIEWER:
                        uiManager.setCurrent(new ViewerView(uiManager));
                        uiManager.run();
                        break;
                    case UserTypes::ADMIN:
                        uiManager.setCurrent(new AdminView(uiManager));
                        uiManager.run();
                        break;
                }
                return;
            }
            else std::cout << "Invalid Combination! Try again.";
            started = true;

        }
        std::cout << HIDE_CURSOR;
    }while(answer != *ESC);
}

void LoginPage::pageOutput() const {
    std::cout << "***** Welcome to StreamZ! *****" << std::endl;
}

