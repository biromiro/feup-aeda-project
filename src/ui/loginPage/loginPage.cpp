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
        if(started) answer = _getch_();
        std::cout << CLEAR_SCREEN << GO_TO_TOP << SHOW_CURSOR;
        pageOutput();
        if(answer != *ESC) {
            std::cout << "Nickname: ";
            getlineCIN(nickname);
            std::cout << "Password: ";
            getlineCIN(password);

            //tries to login
            if (uiManager.getCurrentSession().login(nickname, password)){
                std::cout << CLEAR_SCREEN << GO_TO_TOP << HIDE_CURSOR;

                //sets up the page according to the user who logged in
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

            //could not login
            else std::cerr << "Invalid Combination! Try again.";
            started = true;

        }
        std::cout << HIDE_CURSOR;
    }while(answer != *ESC);
}

void LoginPage::pageOutput() {
    std::cout << "***** Welcome to StreamZ! *****" << std::endl;
}

