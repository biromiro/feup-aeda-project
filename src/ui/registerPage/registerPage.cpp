//
// Created by biromiro on 15/11/20.
//

#include "registerPage.h"

RegisterPage::RegisterPage(UIManager &uiManager) : uiManager(uiManager){}

void RegisterPage::run() {
    char answer = ' ';
    std::string nickname, password;
    do{std::cout << CLEAR_SCREEN << GO_TO_TOP;
        pageOutput();
        std::cout << "What type of account do you wish to create?" << std::endl;
        std::cout << "\n1 - Just a regular viewer!" << std::endl;
        std::cout << "\n2 - I want to stream!" << std::endl;
        std::cout << HIDE_CURSOR;
        answer = _getch_();
        std::cout << SHOW_CURSOR;
        switch (answer) {
            case '1':
                if(viewerRegister()) break;
                else return;
            case '2':
                if(streamerRegister()) break;
                else return;
            default:
                break;
        }
        std::cout << CLEAR_SCREEN << GO_TO_TOP << HIDE_CURSOR;

        if(answer == '1' || answer == '2'){
            //after a successful register, logs in and sends user to the corret UI page (not that ADMIN cannot be formed, so it is not handled)
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

void RegisterPage::pageOutput() {
    std::cout << "***** Welcome to StreamZ! *****" << std::endl;
}

bool RegisterPage::streamerRegister() {
    std::string nickname, name, password;
    Date birthDate = Date();
    char answer = 0;
    do{
        std::cout << CLEAR_SCREEN << GO_TO_TOP;
        getUserInfo(birthDate,name,nickname,password);

        std::cout << CLEAR_SCREEN << GO_TO_TOP;
        std::cout << "Are you happy with your choices?" << std::endl;
        std::cout << "Birth date:" <<  birthDate << "\t" << "Name: " << name << "\n" << "Nickname :" << nickname << "\t" << "Password: " << password << "\n";
        std::cout << "\n1 - I wish to redo my choices" << std::endl;
        std::cout << "0 - Leave and do not save" << std::endl;
        std::cout << "PRESS ANY OTHER KEY TO PROCEED" << std::endl;
        answer = _getch_();
        if(answer != '1') break;

    }while (answer != '0');
    if(answer == '0') return false;
    try{
        auto streamer = uiManager.getPlatform().getStreamerManager()->build(birthDate,name,nickname,password);
    }catch(std::exception& e){
        std::cerr << e.what();
        _getch_();
        return false;
    }
    uiManager.getCurrentSession().login(nickname,password);
    return true;
}

bool RegisterPage::viewerRegister() {
    std::string nickname, name, password;
    Date birthDate = Date();
    bool valid = false;
    char answer = 0;
    do{
        if(valid) answer = _getch_();
        std::cout << CLEAR_SCREEN << GO_TO_TOP;
        getUserInfo(birthDate,name,nickname,password);

        std::cout << CLEAR_SCREEN << GO_TO_TOP;
        std::cout << "Are you happy with your choices?" << std::endl;
        std::cout << "Birth date:" <<  birthDate << "\t" << "Name: " << name << "\n" << "Nickname :" << nickname << "\t" << "Password: " << password << "\n";
        std::cout << "\n1 - I wish to redo my choices" << std::endl;
        std::cout << "PRESS ANY OTHER KEY TO PROCEED" << std::endl;
        answer = _getch_();
        if(answer != '1') break;
        valid = true;
    }while (answer != *ESC);
    if(answer == *ESC) return false;
    try{
        auto viewer = uiManager.getPlatform().getViewerManager()->build(birthDate,name,nickname,password);
    }catch(std::exception& e){
        std::cerr << e.what();
        _getch_();
        return false;
    }
    uiManager.getCurrentSession().login(nickname,password);
    return true;
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
            std::cerr << "Nickname already taken!";
            _getch_();
            continue;
        }
        break;
    }while (true);
    std::cout << "Name: ";
    getlineCIN(name);
    do{
        std::cout << "Password: ";
        getlineCIN(password);
        std::cout << "Please re-enter your password: ";
        getlineCIN(checkPassword);
        if(password != checkPassword){
            std::cerr << "Passwords don't match!";
            _getch_();
            std::cout << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
            continue;
        }else break;
    }while(true);
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
            std::cerr << "That birth date is not valid!";
            _getch_();
            std::cout << CLEAR_LINE << LINE_UP << CLEAR_LINE <<  GO_TO_BEGINNING_OF_LINE;
            continue;
        }else break;
    }while (true);
}

