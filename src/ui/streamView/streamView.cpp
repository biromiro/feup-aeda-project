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
            case '1':
                feedbackToStream();
                break;
            case '2': {
                std::shared_ptr<Viewer> thisViewer;
                thisViewer = uiManager.getPlatform().getViewerManager()->get(
                        uiManager.getCurrentSession().getNickname());
                thisViewer->leaveCurrentStream();
                break;
            }
            default:
                break;
        }
        first = true;
    }while (answer != *ESC && answer != '0');
}

void StreamView::pageOutput() const {
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    std::string nickname = uiManager.getCurrentSession().getNickname();
    auto currentStream = uiManager.getPlatform().getViewerManager()->get(nickname)->getCurrentStream();
    std::cout << "*****StreamZ*****" << nickname << "*****" << std::endl;
    std::cout << "You're watching " << currentStream->getStreamer()->getNickname() << "'s stream!" << std::endl;
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

    char answer = ' ';
    if(thisViewer->getCurrentStream()->getStreamType() == StreamType::PRIVATE){
        std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE <<  LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
        std::cout << "1 - Give Like/Dislike" << std::endl;
        std::cout << "2 - Make a comment" << std::endl;
        std::cout << "0 - Go back to the main menu" << std::endl;
        answer = getch();
        char feedbackAnswer;
        switch (answer) {
            case '1': {
                do {
                    std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE
                              << GO_TO_BEGINNING_OF_LINE;
                    std::cout << "1 - LIKE" << std::endl;
                    std::cout << "2 - DISLIKE" << std::endl;
                    feedbackAnswer = getch();
                    switch (feedbackAnswer) {
                        case '1':
                            thisViewer->getCurrentStream()->addFeedback(FeedbackLikeSystem::LIKE);
                            break;
                        case '2':
                            thisViewer->getCurrentStream()->addFeedback(FeedbackLikeSystem::DISLIKE);
                    }
                } while (feedbackAnswer != '0');
                break;
            }
            case '2': {
                auto privateStream = std::dynamic_pointer_cast<PrivateStream>(thisViewer->getCurrentStream());
                std::string comment;
                bool confirm = false;
                do {
                    std::cout << "Write your comment: ";
                    getline(std::cin, comment);
                    std::cout << "Is this the comment you wish to add (y/n) -> " << comment << std::endl;
                    do {
                        answer = getch();
                        if (answer == 'y' or answer == 'Y') {
                            privateStream->addComment(comment);
                            confirm = true;
                            break;
                        }else if(answer == 'n' or answer == 'N')
                            break;
                    } while (1);
                } while (!confirm);
                break;
            }
        }
    }else{
        std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
        std::cout << "1 - Give Like/Dislike" << std::endl;
        std::cout << "0 - Go back to the main menu" << std::endl;
        answer = getch();
        if(answer == '1') {
                std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE
                          << GO_TO_BEGINNING_OF_LINE;
                std::cout << "1 - LIKE" << std::endl;
                std::cout << "2 - DISLIKE" << std::endl;
                char feedbackAnswer = getch();
                switch (feedbackAnswer) {
                    case '1':
                        thisViewer->getCurrentStream()->addFeedback(FeedbackLikeSystem::LIKE);
                        break;
                    case '2':
                        thisViewer->getCurrentStream()->addFeedback(FeedbackLikeSystem::DISLIKE);
                }
        }
    }
}
