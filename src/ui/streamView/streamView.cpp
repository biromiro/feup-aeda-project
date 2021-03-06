//
// Created by biromiro on 15/11/20.
//

#include "streamView.h"

StreamView::StreamView(UIManager &uiManager) : uiManager(uiManager){}

void StreamView::run() {
    char answer ;
    do{
        pageOutput();
        answer = _getch_();
        switch (answer) {
            case '1':
                feedbackToStream();
                break;
            case '2': {
                std::shared_ptr<Viewer> thisViewer;
                thisViewer = uiManager.getPlatform().getViewerManager()->get(
                        uiManager.getCurrentSession().getNickname());
                thisViewer->leaveCurrentStream();
                answer = '0';
                break;
            }
            default:
                break;
        }
    }while (answer != *ESC && answer != '0');
}

void StreamView::pageOutput() const {
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    std::string nickname = uiManager.getCurrentSession().getNickname();
    auto currentStream = uiManager.getPlatform().getViewerManager()->get(nickname)->getCurrentStream();
    std::cout << "*****StreamZ*****" << nickname << "*****" << std::endl;
    std::cout << "\nYou're watching " << currentStream->getStreamer()->getNickname() << "'s stream!" << std::endl;
    std::cout << "\n--Stream Info--\nTitle   " << currentStream->getTitle() << "\nGenre   " <<
                currentStream->getGenre() << "\nLanguage   " << currentStream->getLanguage() << std::endl;
    std::cout << "\n1 - Give feedback!" << std::endl;
    std::cout << "2 - Leave the current stream" << std::endl;
    std::cout << "0 - Go back to the main menu!" << std::endl;
}

void StreamView::feedbackToStream() {
    std::shared_ptr<Viewer> thisViewer;
    thisViewer = uiManager.getPlatform().getViewerManager()->get(
            uiManager.getCurrentSession().getNickname());

    char answer;
    if(thisViewer->getCurrentStream()->getStreamType() == StreamType::PRIVATE){
        std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE <<  LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
        std::cout << "1 - Give Like/Dislike" << std::endl;
        std::cout << "2 - Make a comment" << std::endl;
        std::cout << "0 - Go back to the main menu" << std::endl;
        answer = _getch_();
        char feedbackAnswer;
        switch (answer) {
            case '1': {
                std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE <<
                LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
                std::cout << "1 - LIKE" << std::endl;
                std::cout << "2 - DISLIKE" << std::endl;
                feedbackAnswer = _getch_();
                switch (feedbackAnswer) {
                    case '1':
                        thisViewer->giveFeedbackToStream(FeedbackLikeSystem::LIKE);
                        break;
                    case '2':
                        thisViewer->giveFeedbackToStream(FeedbackLikeSystem::DISLIKE);
                    }
                break;
            }
            case '2': {
                std::string comment;
                bool confirm = false;
                do {
                    std::cout << "Write your comment: ";
                    getlineCIN(comment);
                    std::cout << "Is this the comment you wish to add (y/n) -> " << comment << std::endl;
                    do {
                        answer = _getch_();
                        if (answer == 'y' or answer == 'Y') {
                            thisViewer->giveFeedbackToStream(comment);
                            confirm = true;
                            break;
                        }else if(answer == 'n' or answer == 'N')
                            break;
                    } while (true);
                } while (!confirm);
                break;
            }
        }
    }else{
        std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
        std::cout << "1 - Give Like/Dislike" << std::endl;
        std::cout << "0 - Go back " << std::endl;
        answer = _getch_();
        if(answer == '1') {
                std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE
                          << GO_TO_BEGINNING_OF_LINE;
                std::cout << "1 - LIKE" << std::endl;
                std::cout << "2 - DISLIKE" << std::endl;
                char feedbackAnswer = _getch_();
                switch (feedbackAnswer) {
                    case '1':
                        thisViewer->giveFeedbackToStream(FeedbackLikeSystem::LIKE);
                        break;
                    case '2':
                        thisViewer->giveFeedbackToStream(FeedbackLikeSystem::DISLIKE);
                }
        }
    }
}
