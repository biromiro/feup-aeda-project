//
// Created by biromiro on 15/11/20.
//

#include "registerPage.h"

RegisterPage::RegisterPage(UIManager &uiManager) : uiManager(uiManager){}

void RegisterPage::run() {
    char answer = ' ';
    bool started = false;
    std::string nickname, password;
    do{
        if(started) answer = getch();
        std::cout << CLEAR_SCREEN << GO_TO_TOP;
        pageOutput();
        if(answer != *ESC) {
            std::cout << "What type of account do you wish to create?" << std::endl;
            std::cout << "\n1 - Just a regular viewer!" << std::endl;
            std::cout << "\n2 - I want to stream!" << std::endl;
            std::cout << HIDE_CURSOR;
            answer = getch();
            std::cout << SHOW_CURSOR;
            switch (answer) {
                case '1':
                    viewerRegister();
                    return;
                case '2':
                    streamerRegister();
                    return;
                default:
                    started = true;
                    break;
            }
            std::cout << CLEAR_SCREEN << GO_TO_TOP << HIDE_CURSOR;
            switch (uiManager.getCurrentSession().getCurrentUser()->getUserType()) {
                case UserTypes::STREAMER:
                    uiManager.setCurrent(new StreamerView(uiManager));
                    uiManager.run();
                    return;
                case UserTypes::VIEWER:
                    uiManager.setCurrent(new ViewerView(uiManager));
                    uiManager.run();
                    return;
            }
        }
    }while(answer != *ESC);
}

void RegisterPage::pageOutput() const {
    std::cout << "***** Welcome to StreamZ! *****" << std::endl;
}

bool RegisterPage::streamerRegister() {
    std::string nickname, name, password;
    Date birthDate = Date(), currentDate = Date();
    bool valid = false;
    char answer;
    do{
        if(valid) answer = getch();
        std::cout << CLEAR_SCREEN << GO_TO_TOP;
        getUserInfo(birthDate,name,nickname,password);
        if(timeElapsed(currentDate,birthDate).getYear() < 15){
            std::cout << "You have to be at least 15 years old!" << std::endl;
            getch();
            continue;
        }
        std::cout << CLEAR_SCREEN << GO_TO_TOP;
        std::cout << "Are you happy with your choices?" << std::endl;
        std::cout << "Birth date:" <<  birthDate << "\t" << "Name: " << name << "\n" << "Nickname :" << nickname << "\t" << "Password: " << password << "\n";
        std::cout << "\n1 - I wish to redo my choices" << std::endl;
        std::cout << "PRESS ANY OTHER KEY TO PROCEED" << std::endl;
        answer = getch();
        if(answer != '1') break;
        valid = true;
    }while (answer != *ESC);
    if(answer == *ESC) return false;
    auto streamer = uiManager.getPlatform().getStreamerManager()->build(birthDate,name,nickname,password);
    uiManager.getCurrentSession().login(nickname,password);
}

bool RegisterPage::viewerRegister() {
    std::string nickname, name, password;
    Date birthDate = Date(), currentDate = Date();
    bool valid = false;
    char answer;
    do{
        if(valid) answer = getch();
        std::cout << CLEAR_SCREEN << GO_TO_TOP;
        getUserInfo(birthDate,name,nickname,password);
        if(timeElapsed(currentDate,birthDate).getYear() < 12){
            std::cout << "You have to be at least 12 years old!" << std::endl;
            getch();
            continue;
        }
        std::cout << CLEAR_SCREEN << GO_TO_TOP;
        std::cout << "Are you happy with your choices?" << std::endl;
        std::cout << "Birth date:" <<  birthDate << "\t" << "Name: " << name << "\n" << "Nickname :" << nickname << "\t" << "Password: " << password << "\n";
        std::cout << "\n1 - I wish to redo my choices" << std::endl;
        std::cout << "PRESS ANY OTHER KEY TO PROCEED" << std::endl;
        answer = getch();
        if(answer != '1') break;
        valid = true;
    }while (answer != *ESC);
    if(answer == *ESC) return false;
    auto viewer = uiManager.getPlatform().getViewerManager()->build(birthDate,name,nickname,password);
    uiManager.getCurrentSession().login(nickname,password);
}


void RegisterPage::getUserInfo(Date& birthDate, std::string& name, std::string& nickname, std::string& password){
    std::string checkPassword;
    unsigned year, month, day;
    do{
        std::cout << CLEAR_SCREEN << GO_TO_TOP;
        pageOutput();
        std::cout << "\nPlease enter the following information:" << std::endl;
        std::cout << "\nNickname: ";
        getlineCIN(nickname);
        if(uiManager.getPlatform().getUserManager()->has(nickname)){
            std::cout << "Nickname already taken!";
            getch();
            continue;
        }
        break;
    }while (1);
    std::cout << "Name: ";
    getlineCIN(name);
    do{
        std::cout << "Password: ";
        getlineCIN(password);
        std::cout << "Please re-enter your password: ";
        getlineCIN(checkPassword);
        if(password != checkPassword){
            std::cout << "Passwords don't match!";
            getch();
            std::cout << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
            continue;
        }else break;
    }while(1);
    do {
        std::cout << "Please insert your birthdate:" << std::endl;
        do{
            std::cout << "Year: ";
            year = inputNumber();
            std::cout << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
        }while (year == 0);
        do{
            std::cout << "Month: ";
            month = inputNumber();
            std::cout << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
        }while (month == 0);
        do{
            std::cout << "Day: ";
            day = inputNumber();
            std::cout << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
        }while (day == 0);
        birthDate.setDate(year,month,day);
        if(!birthDate.isValid()){
            std::cout << "That birth date is not valid!";
            getch();
            std::cout << CLEAR_LINE << LINE_UP << CLEAR_LINE <<  GO_TO_BEGINNING_OF_LINE;
            continue;
        }else break;
    }while (1);
}

