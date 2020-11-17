//
// Created by biromiro on 15/11/20.
//

#include "viewerView.h"

ViewerView::ViewerView(UIManager &uiManager) : uiManager(uiManager){}

void ViewerView::run() {
    pageOutput();
    char answer = getch();
    bool started = false;
    do{
        if(started) answer = getch();
        switch (answer) {
            case '1':
                chooseStream();
                break;
            case '2':
                searchNewStreamers();
                break;
            case '3':
                followingStreamers();
                break;
            case '0':
                uiManager.getCurrentSession().logout();
                break;
            default:
                break;
        }
        started = true;

    }while (answer != '0');
}



void ViewerView::pageOutput() const {
    std::cout << "*****StreamZ*****" << uiManager.getCurrentSession().getNickname() << "*****" << std::endl;
    std::cout << "1 - Choose a stream to watch!" << std::endl;
    std::cout << "2 - Search for new streamers" << std::endl;
    std::cout << "3 - Who am I following?" << std::endl;
    std::cout << "0 - Logout - " << std::endl;
}

void ViewerView::chooseStream() {

}

void ViewerView::searchNewStreamers() {

}

void ViewerView::followingStreamers() {

}

