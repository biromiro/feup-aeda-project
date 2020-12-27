//
// Created by biromiro on 15/11/20.
//

#include "viewerView.h"
#include "../leaderboardPage/leaderboardPage.h"

ViewerView::ViewerView(UIManager &uiManager) : uiManager(uiManager){}

void ViewerView::run() {
    char answer;
    do{
        std::cout << CLEAR_SCREEN << GO_TO_TOP << HIDE_CURSOR;
        pageOutput();
        std::cout << "1 - Choose a stream to watch!" << std::endl;
        std::cout << "2 - Search for new streamers" << std::endl;
        std::cout << "3 - Following Streamers, Donations and Merch Requests" << std::endl;
        std::cout << "4 - What streams are available?" << std::endl;
        std::cout << "5 - My stream history" << std::endl;
        std::cout << "6 - Let me check the leaderboards!" << std::endl;
        std::cout << "7 - Account Settings" << std::endl;
        std::cout << "0 - Logout" << std::endl;
        answer = _getch_();
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
            case '7': {
                bool leave = accountSettings();
                if (leave) answer = '0';}
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
        _getch_();
    } else {
        unsigned int streamID;
        do{
            std::cout << CLEAR_SCREEN << GO_TO_TOP << HIDE_CURSOR;
            pageOutput();
            std::cout << "Please input the streamID of which you wish to join (0 to return to main menu): " << SHOW_CURSOR << std::endl;
            streamID = inputNumber();
            if(streamID == 0) return;
            std::shared_ptr<Stream> streamToJoin;
            try{
                streamToJoin = uiManager.getPlatform().getStreamManager()->get(streamID);
            } catch (std::exception& exception) {
                std::cerr << exception.what();
                _getch_();
            }
            if(streamToJoin != nullptr){
                try{
                    thisViewer->joinStream(streamToJoin);
                }catch(std::exception& e){
                    std::cerr << e.what();
                    _getch_();
                }
                if(streamToJoin->getStreamType() == StreamType::PRIVATE && !thisViewer->isWatchingStream()){
                    std::cerr << "You're not in the whitelist of this stream!" << std::endl;
                    _getch_();
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
    char answer;
    std::cout << "\n 1 - Follow a streamer!" << std::endl;
    std::cout << "\n 0 - Go to main menu" << std::endl;
    do{
        answer = _getch_();
        switch (answer) {
            case '1':
                std::string nicknameToFollow;
                auto thisViewer = uiManager.getPlatform().getViewerManager()->get(uiManager.getCurrentSession().getNickname());
                std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE <<  LINE_UP << CLEAR_LINE  <<  LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
                std::cout << "Who do you wish to follow?";
                getlineCIN(nicknameToFollow);
                auto streamerToFollow = uiManager.getPlatform().getStreamerManager()->get(nicknameToFollow);

                if(streamerToFollow != nullptr){
                    if(thisViewer->followStreamer(streamerToFollow)){
                        std::cout << "Successfully followed!";
                        _getch_();
                        answer = '0';
                    }else{
                        std::cerr << "You already follow this streamer!" << std::endl;
                        _getch_();
                        std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                        std::cout << "\n 1 - Follow a streamer!" << std::endl;
                        std::cout << "\n 0 - Go to main menu" << std::endl;
                    }
                }else{
                    std::cerr << "There's no such streamer!" << std::endl;
                    _getch_();
                    std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                    std::cout << "\n 1 - Follow a streamer!" << std::endl;
                    std::cout << "\n 0 - Go to main menu" << std::endl;
                }
                break;
        }
    }while (answer != '0' && answer != *ESC);
}

void ViewerView::followingStreamerActions(){
    char answer;
    std::cout << "\n 1 - Unfollow a streamer!" << std::endl;
    std::cout << "\n 2 - Donate to a streamer!" << std::endl;
    std::cout << "\n 3 - Do a merch request!" << std::endl;
    std::cout << "\n 4 - Remove a previous merch request!" << std::endl;
    std::cout << "\n 0 - Go to main menu" << std::endl;
    do{
        answer = _getch_();
        switch (answer) {
            case '1':{
                std::string nicknameToUnfollow;
                auto thisViewer = uiManager.getPlatform().getViewerManager()->get(
                        uiManager.getCurrentSession().getNickname());
                std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP
                          << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                std::cout << "Who do you wish to unfollow?";
                getlineCIN(nicknameToUnfollow);
                auto streamerToUnfollow = uiManager.getPlatform().getStreamerManager()->get(nicknameToUnfollow);
                if (streamerToUnfollow != nullptr) {
                    if (thisViewer->unfollowStreamer(streamerToUnfollow)) {
                        try{
                            streamerToUnfollow->removeMerchOrder(uiManager.getCurrentSession().getNickname());
                        } catch (std::exception &e) {
                        }
                        std::cout << "Successfully unfollowed!";
                        _getch_();
                        answer = '0';
                    } else {
                        std::cerr << "You do not follow this streamer!" << std::endl;
                        _getch_();
                        std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP
                                  << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                        std::cout << "\n 1 - Unfollow a streamer!" << std::endl;
                        std::cout << "\n 2 - Donate to a streamer!" << std::endl;
                        std::cout << "\n 3 - Do a merch request!" << std::endl;
                        std::cout << "\n 4 - Remove a previous merch request!" << std::endl;
                        std::cout << "\n 0 - Go to main menu" << std::endl;
                    }
                } else {
                    std::cerr << "There's no such streamer!" << std::endl;
                    _getch_();
                    std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP
                              << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                    std::cout << "\n 1 - Unfollow a streamer!" << std::endl;
                    std::cout << "\n 2 - Donate to a streamer!" << std::endl;
                    std::cout << "\n 3 - Do a merch request!" << std::endl;
                    std::cout << "\n 4 - Remove a previous merch request!" << std::endl;
                    std::cout << "\n 0 - Go to main menu" << std::endl;
                }
                break;
            }case '2': {
                std::string nicknameToDonate;
                auto thisViewer = uiManager.getPlatform().getViewerManager()->get(
                        uiManager.getCurrentSession().getNickname());
                std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP
                          << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                std::cout << "Who do you wish to donate to?";
                getlineCIN(nicknameToDonate);
                auto streamerToUnfollow = uiManager.getPlatform().getStreamerManager()->get(nicknameToDonate);
                if (streamerToUnfollow != nullptr) {
                    if (thisViewer->unfollowStreamer(streamerToUnfollow)) {
                        thisViewer->followStreamer(streamerToUnfollow);
                        float donationAmmount = 0;
                        unsigned int val = 0;
                        do{
                            std::cout << "Donation Ammount: ";
                            donationAmmount = inputFloat();
                            std::cout << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
                        }while(donationAmmount <= 0.0);
                        do{
                            std::cout << "Rate the streamer (1-5): ";
                            val = inputNumber();
                            std::cout << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
                        }while(val < 1 || val > 5);
                        auto value = static_cast<streamerWorkRating>(val-1);
                        uiManager.getPlatform().getStreamerManager()->addNewDonation(nicknameToDonate, donationAmmount, value);
                        std::cout << "Successfully donated!";
                        _getch_();
                        answer = '0';
                    } else {
                        std::cerr << "You do not follow this streamer!" << std::endl;
                        _getch_();
                        std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP
                                  << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                        std::cout << "\n 1 - Unfollow a streamer!" << std::endl;
                        std::cout << "\n 2 - Donate to a streamer!" << std::endl;
                        std::cout << "\n 3 - Do a merch request!" << std::endl;
                        std::cout << "\n 4 - Remove a previous merch request!" << std::endl;
                        std::cout << "\n 0 - Go to main menu" << std::endl;
                    }
                } else {
                    std::cerr << "There's no such streamer!" << std::endl;
                    _getch_();
                    std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP
                              << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                    std::cout << "\n 1 - Unfollow a streamer!" << std::endl;
                    std::cout << "\n 2 - Donate to a streamer!" << std::endl;
                    std::cout << "\n 3 - Do a merch request!" << std::endl;
                    std::cout << "\n 4 - Remove a previous merch request!" << std::endl;
                    std::cout << "\n 0 - Go to main menu" << std::endl;
                }
                break;
            }case '3': {
                std::string nicknameToRequest;
                auto thisViewer = uiManager.getPlatform().getViewerManager()->get(
                        uiManager.getCurrentSession().getNickname());
                std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP
                          << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                std::cout << "Who do you wish to request merch from?";
                getlineCIN(nicknameToRequest);
                auto streamerToUnfollow = uiManager.getPlatform().getStreamerManager()->get(nicknameToRequest);
                if (streamerToUnfollow != nullptr) {
                    if (thisViewer->unfollowStreamer(streamerToUnfollow)) {
                        thisViewer->followStreamer(streamerToUnfollow);
                        unsigned int numProducts = 0, buyAvailability = 0;
                        do{
                            std::cout << "How many products do you wish to buy? ";
                            numProducts = inputNumber();
                            std::cout << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
                        }while(numProducts == 0);
                        do{
                            std::cout << "How available are you to buy (1-5)?  ";
                            buyAvailability = inputNumber();
                            std::cout << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
                        }while(buyAvailability < 1 || buyAvailability > 5);
                        MerchRequest merchRequest(uiManager.getCurrentSession().getNickname(), numProducts, buyAvailability);
                        try{
                            streamerToUnfollow->addMerchOrder(merchRequest);
                        } catch (std::exception &e) {
                            std::cerr << e.what();
                            break;
                        }
                        std::cout << "Successfully donated!";
                        _getch_();
                        answer = '0';
                    } else {
                        std::cerr << "You do not follow this streamer!" << std::endl;
                        _getch_();
                        std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP
                                  << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                        std::cout << "\n 1 - Unfollow a streamer!" << std::endl;
                        std::cout << "\n 2 - Donate to a streamer!" << std::endl;
                        std::cout << "\n 3 - Do a merch request!" << std::endl;
                        std::cout << "\n 4 - Remove a previous merch request!" << std::endl;
                        std::cout << "\n 0 - Go to main menu" << std::endl;
                    }
                } else {
                    std::cerr << "There's no such streamer!" << std::endl;
                    _getch_();
                    std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP
                              << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                    std::cout << "\n 1 - Unfollow a streamer!" << std::endl;
                    std::cout << "\n 2 - Donate to a streamer!" << std::endl;
                    std::cout << "\n 3 - Do a merch request!" << std::endl;
                    std::cout << "\n 4 - Remove a previous merch request!" << std::endl;
                    std::cout << "\n 0 - Go to main menu" << std::endl;
                }
                break;
            }case '4': {
                std::string nicknameToRequest;
                auto thisViewer = uiManager.getPlatform().getViewerManager()->get(
                        uiManager.getCurrentSession().getNickname());
                std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP
                          << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                std::cout << "Who do you wish to remove the merch request from?";
                getlineCIN(nicknameToRequest);
                auto streamerToUnfollow = uiManager.getPlatform().getStreamerManager()->get(nicknameToRequest);
                if (streamerToUnfollow != nullptr) {
                    if (thisViewer->unfollowStreamer(streamerToUnfollow)) {
                        thisViewer->followStreamer(streamerToUnfollow);
                        try{
                            streamerToUnfollow->removeMerchOrder(uiManager.getCurrentSession().getNickname());
                        } catch (std::exception &e) {
                            std::cerr << e.what();
                            break;
                        }
                        std::cout << "Successfully removed!";
                        _getch_();
                        answer = '0';
                    } else {
                        std::cerr << "You do not follow this streamer!" << std::endl;
                        _getch_();
                        std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP
                                  << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                        std::cout << "\n 1 - Unfollow a streamer!" << std::endl;
                        std::cout << "\n 2 - Donate to a streamer!" << std::endl;
                        std::cout << "\n 3 - Do a merch request!" << std::endl;
                        std::cout << "\n 4 - Remove a previous merch request!" << std::endl;
                        std::cout << "\n 0 - Go to main menu" << std::endl;
                    }
                } else {
                    std::cerr << "There's no such streamer!" << std::endl;
                    _getch_();
                    std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP
                              << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                    std::cout << "\n 1 - Unfollow a streamer!" << std::endl;
                    std::cout << "\n 2 - Donate to a streamer!" << std::endl;
                    std::cout << "\n 3 - Do a merch request!" << std::endl;
                    std::cout << "\n 4 - Remove a previous merch request!" << std::endl;
                    std::cout << "\n 0 - Go to main menu" << std::endl;
                }
                break;
            }
        }
    }while (answer != '0' && answer != *ESC);
}

void ViewerView::showAvailableStreams() {
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();
    std::cout << Leaderboard<std::shared_ptr<Stream>>(uiManager.getPlatform().getStreamManager()->getStreams());
    std::cout << "Press any key to go to the main menu!" << std::endl;
    _getch_();
}

void ViewerView::myViewHistory() {
    auto thisViewer = uiManager.getPlatform().getViewerManager()->get(uiManager.getCurrentSession().getNickname());
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();
    std::vector<std::shared_ptr<Stream>> keys;
    for(auto it = thisViewer->getStreamHistory().begin(); it != thisViewer->getStreamHistory().end(); ++it)
        keys.push_back(it->first);
    auto viewerHistory = Leaderboard<std::shared_ptr<Stream>>(keys);
    std::cout << viewerHistory;
    std::cout << "Press any key to go to the main menu!" << std::endl;
    _getch_();
}

bool ViewerView::accountSettings() {
    char answer;
    std::cout << "\n 1 - Deactivate my account" << std::endl;
    std::cout << "\n 0 - Go to main menu" << std::endl;
    do{
        answer = _getch_();
        switch (answer) {
            case '1': {
                std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP
                          << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                std::cout << "Do you really wish to deactivate your account? (press Y to confirm)";
                answer = _getch_();
                if (answer == 'y' || answer == 'Y') {
                    uiManager.getCurrentSession().getCurrentUser()->deactivateAcc();
                    std::shared_ptr<Viewer> viewer;
                    viewer = uiManager.getPlatform().getViewerManager()->get(
                            uiManager.getCurrentSession().getNickname());
                    viewer->leaveCurrentStream();
                    if(viewer->isWatchingStream()){
                        viewer->leaveCurrentStream();
                    }
                    return true;
                } else break;
            }
        }
    }while (answer != '0' && answer != *ESC);
    return false;
}
