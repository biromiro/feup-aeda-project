//
// Created by biromiro on 15/11/20.
//

#include "streamView.h"

StreamView::StreamView(UIManager &uiManager) : uiManager(uiManager){}

void StreamView::run() {
    pageOutput();
    char answer = getch();
    bool first = false;
    do{
        if(first) answer = getch();
        switch (answer) {
            default:
                break;
        }
        first = true;
    }while (answer != *ESC);
}

void StreamView::pageOutput() const {
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    std::string nickname = uiManager.getCurrentSession().getNickname();
    auto currentStream = uiManager.getPlatform().getViewerManager()->get(nickname)->getCurrentStream();
    std::cout << "*****StreamZ*****" << nickname << "*****" << std::endl;
    std::cout << "You're watching " << currentStream->getStreamer()->getNickname() << "'s stream!" << std::endl;
    std::cout << "\n--Stream Info--\nTitle   " << currentStream->getTitle() << "\nGenre   " <<
                currentStream->getGenre() << "\nLanguage   " << currentStream->getLanguage() << std::endl;
}
