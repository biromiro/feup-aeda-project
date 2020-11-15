//
// Created by nrtc on 14/11/2020.
//

#include "initialPage.h"

InitialPage::InitialPage(UIManager& uiManager) : uiManager(uiManager) {}

void InitialPage::run() {
    char answer;
    do{
        pageOutput();
        answer = getch();
        switch (answer) {
            case '1':
                break;
            case '2':
                break;
            default:
                break;
        }
        std::cout << "\033[2J\033[1;1H";
    }while(answer != '0');
}

void InitialPage::pageOutput() const{
    std::cout << "***** Welcome to StreamZ! *****" << std::endl;
    std::cout << "\n\t1 - Login" << std::endl;
    std::cout << "\t2 - Register" << std::endl;
    std::cout << "\t0 - Exit" << std::endl;
    std::cout << "\n********************************" << std::endl;
    std::cout << "Choice: ";
}

