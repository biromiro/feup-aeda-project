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
            //std::cin.ignore();
            std::cout << "Nickname: ";
            getline(std::cin, nickname);
            std::cout << "Password: ";
            getline(std::cin, password);
            if (uiManager.getCurrentSession().login(nickname, password)){
                std::cout << HIDE_CURSOR;
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
