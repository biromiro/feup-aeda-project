//
// Created by biromiro on 15/11/20.
//

#include "viewerView.h"
#include "../leaderboardPage/leaderboardPage.h"

ViewerView::ViewerView(UIManager &uiManager) : uiManager(uiManager){}

void ViewerView::run() {
    char answer = ' ';
    do{
        std::cout << CLEAR_SCREEN << GO_TO_TOP << HIDE_CURSOR;
        pageOutput();
        std::cout << "1 - Choose a stream to watch!" << std::endl;
        std::cout << "2 - Search for new streamers" << std::endl;
        std::cout << "3 - Who am I following?" << std::endl;
        std::cout << "4 - What streams are available?" << std::endl;
        std::cout << "5 - My stream history" << std::endl;
        std::cout << "6 - Let me check the leaderboards!" << std::endl;
        std::cout << "0 - Logout" << std::endl;
        answer = getch();
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
            case '4':
                showAvailableStreams();
                break;
            case '5':
                myViewHistory();
                break;
            case '6':
                uiManager.setCurrent(new LeaderboardPage(uiManager));
                uiManager.run();
                break;
            case '0':
                uiManager.getCurrentSession().logout();
                break;
            default:
                break;
        }

    }while (answer != '0');
}



void ViewerView::pageOutput() const {
    std::cout << "*****StreamZ*****" << uiManager.getCurrentSession().getNickname() << "*****" << std::endl;
}

void ViewerView::chooseStream() {
    auto user = uiManager.getCurrentSession().getCurrentUser();
    auto thisViewer = uiManager.getPlatform().getViewerManager()->get(user->getNickname());
    if(thisViewer->isWatchingStream()){
        std::cout << CLEAR_SCREEN << GO_TO_TOP << HIDE_CURSOR;
        pageOutput();
        std::cout << "You are already watching a stream! Redirecting..." << std::endl;
        getch();
    } else {
        unsigned int streamID;
        do{
            std::cout << CLEAR_SCREEN << GO_TO_TOP << HIDE_CURSOR;
            pageOutput();
            std::cout << "Please input the streamID of which you wish to join (0 to return to main menu): " << SHOW_CURSOR << std::endl;
            streamID = inputNumber();
            if(streamID == 0) return;
            auto streamToJoin = uiManager.getPlatform().getStreamManager()->get(streamID);
            if(streamToJoin != nullptr){
                thisViewer->joinStream(streamToJoin);
                if(streamToJoin->getStreamType() == StreamType::PRIVATE && !thisViewer->isWatchingStream()){
                    std::cout << HIDE_CURSOR << "You're not in the whitelist of this stream!" << std::endl;
                    getch();
                }
            }
        }while (!(thisViewer->isWatchingStream()));

    }
    uiManager.setCurrent(new StreamView(uiManager));
    uiManager.run();
}

void ViewerView::searchNewStreamers() {
    auto thisViewer = uiManager.getPlatform().getViewerManager()->get(uiManager.getCurrentSession().getNickname());
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();
    std::cout << uiManager.getPlatform().getLeaderboardManager()->getNotFollowingStreamersLeaderboard(thisViewer) << std::endl;
    newStreamerActions();
}

void ViewerView::followingStreamers() {
    auto thisViewer = uiManager.getPlatform().getViewerManager()->get(uiManager.getCurrentSession().getNickname());
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();
    std::cout << uiManager.getPlatform().getLeaderboardManager()->getFollowingStreamersLeaderboard(thisViewer) << std::endl;
    followingStreamerActions();
}

void ViewerView::newStreamerActions(){
    char answer = ' ';
    std::cout << "\n 1 - Follow a streamer!" << std::endl;
    std::cout << "\n 0 - Go to main menu" << std::endl;
    do{
        answer = getch();
        switch (answer) {
            case '1':
                std::string nicknameToFollow;
                auto thisViewer = uiManager.getPlatform().getViewerManager()->get(uiManager.getCurrentSession().getNickname());
                std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE <<  LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
                std::cout << "Who do you wish to follow?";
                getline(std::cin,nicknameToFollow);
                auto streamerToFollow = uiManager.getPlatform().getStreamerManager()->get(nicknameToFollow);

                if(streamerToFollow != nullptr){
                    if(thisViewer->followStreamer(streamerToFollow)){
                        std::cout << "Successfully followed!";
                        getch();
                        answer = '0';
                    }else{
                        std::cout << "You already follow this streamer!" << std::endl;
                        getch();
                        std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                        std::cout << "\n 1 - Follow a streamer!" << std::endl;
                        std::cout << "\n 0 - Go to main menu" << std::endl;
                    }
                }else{
                    std::cout << "There's no such streamer!" << std::endl;
                    getch();
                    std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                    std::cout << "\n 1 - Follow a streamer!" << std::endl;
                    std::cout << "\n 0 - Go to main menu" << std::endl;
                }

                break;
        }
    }while (answer != '0' && answer != *ESC);
}

void ViewerView::followingStreamerActions(){
    char answer = ' ';
    std::cout << "\n 1 - Follow a streamer!" << std::endl;
    std::cout << "\n 0 - Go to main menu" << std::endl;
    do{
        answer = getch();
        switch (answer) {
            case '1':
                std::string nicknameToUnfollow;
                auto thisViewer = uiManager.getPlatform().getViewerManager()->get(uiManager.getCurrentSession().getNickname());
                std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE <<  LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
                std::cout << "Who do you wish to unfollow?";
                getline(std::cin,nicknameToUnfollow);
                auto streamerToUnfollow = uiManager.getPlatform().getStreamerManager()->get(nicknameToUnfollow);

                if(streamerToUnfollow != nullptr){
                    if(thisViewer->unfollowStreamer(streamerToUnfollow)){
                       std::cout << "Successfully unfollowed!";
                        getch();
                        answer = '0';
                    }else{
                        std::cout << "You do not follow this streamer!" << std::endl;
                        getch();
                        std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                        std::cout << "\n 1 - Follow a streamer!" << std::endl;
                        std::cout << "\n 0 - Go to main menu" << std::endl;
                    }
                }else{
                    std::cout << "There's no such streamer!" << std::endl;
                    getch();
                    std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                    std::cout << "\n 1 - Follow a streamer!" << std::endl;
                    std::cout << "\n 0 - Go to main menu" << std::endl;
                }

                break;
        }
    }while (answer != '0' && answer != *ESC);
}

void ViewerView::showAvailableStreams() {
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();
    std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreams();
    std::cout << "Press any key to go to the main menu!" << std::endl;
    getch();
}

void ViewerView::myViewHistory() {
    auto thisViewer = uiManager.getPlatform().getViewerManager()->get(uiManager.getCurrentSession().getNickname());
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();
    auto viewerHistory = Leaderboard<std::shared_ptr<Stream>>(thisViewer->getStreamHistory());
    std::cout << viewerHistory;
    std::cout << "Press any key to go to the main menu!" << std::endl;
    getch();
}
