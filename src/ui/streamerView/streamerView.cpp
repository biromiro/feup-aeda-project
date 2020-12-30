//
// Created by biromiro on 15/11/20.
//

#include "streamerView.h"
#include "../leaderboardPage/leaderboardPage.h"

StreamerView::StreamerView(UIManager &uiManager) : uiManager(uiManager){}

void StreamerView::run() {
    char answer;
    do{
        std::cout << CLEAR_SCREEN << GO_TO_TOP << HIDE_CURSOR;
        pageOutput();
        std::cout << "1 - Start a stream!" << std::endl;
        std::cout << "2 - See stream statistics" << std::endl;
        std::cout << "3 - Who is old enough to join my stream?" << std::endl;
        std::cout << "4 - Add viewers to the whitelist" << std::endl;
        std::cout << "5 - Finish current stream" << std::endl;
        std::cout << "6 - Let me see my past streams!" << std::endl;
        std::cout << "7 - Let me check the leaderboards!" << std::endl;
        std::cout << "8 - Handle Merch System" << std::endl;
        std::cout << "9 - Account Settings" << std::endl;
        std::cout << "0 - Logout" << std::endl;
        answer = _getch_();
        switch (answer) {
            case '1':
                startStream();
                break;
            case '2':
                seeStreamStatistics();
                break;
            case '3':
                oldEnoughViewerLB();
                break;
            case '4':
                addViewersToWhitelist();
                break;
            case '5':
                finishCurrentStream();
                break;
            case '6':
                checkPastStreams();
                break;
            case '7':
                uiManager.setCurrent(new LeaderboardPage(uiManager));
                uiManager.run();
                break;
            case '8':
                merchSystem();
                break;
            case '9':{
                bool leave = accountSettings();
                if(leave) answer = '0';
                break;}
            case '0':
                uiManager.getCurrentSession().logout();
                break;
            default:
                break;
        }

    }while (answer != '0');
}

void StreamerView::pageOutput() const {
    std::cout << "*****StreamZ*****" << uiManager.getCurrentSession().getNickname() << "*****" << std::endl;
    auto thisStreamer = uiManager.getPlatform().getStreamerManager()->get(uiManager.getCurrentSession().getNickname());
    if(thisStreamer->isStreaming()){
        auto currentStream = uiManager.getPlatform().getStreamManager()->get(thisStreamer->getCurrentStreamID());
        std::cout << "\n YOU'RE LIVE -> " << uiManager.getPlatform().getStreamManager()->get(thisStreamer->getCurrentStreamID())->getTitle()
                  << " <- *" << currentStream->getNumOfViewers() << "*" << std::endl;
    }
    std::cout << "\n";
}

void StreamerView::startStream() {
    auto thisStreamer = uiManager.getPlatform().getStreamerManager()->get(uiManager.getCurrentSession().getNickname());
    if(thisStreamer->isStreaming()){
        std::cout << CLEAR_SCREEN << GO_TO_TOP;
        pageOutput();
        std::cerr << "You are already streaming! Press any key to go back" << std::endl;
        _getch_();
    }else{
        char answer;
        do{
            std::string title;
            StreamLanguage language = StreamLanguage::INVALID;
            unsigned int minimumAge, maxNumOfViewers = 0;
            StreamType type = StreamType::INVALID;
            StreamGenre genre = StreamGenre::INVALID;
            std::cout << CLEAR_SCREEN << GO_TO_TOP;
            pageOutput();
            std::cout << "\nPlease enter the following information:" << std::endl;
            std::cout << "\nTitle: ";
            getlineCIN(title);
            do{
                std::cout << "Language (Abbreviation, like PT_PT for Portugal's Portuguese or EN for English): ";
                std::cin >> language;
                std::cout << CLEAR_LINE << LINE_UP << CLEAR_LINE <<  GO_TO_BEGINNING_OF_LINE;
            }while (language == StreamLanguage::INVALID);

            do{
                std::cout << "Minimum Age: ";
                minimumAge = inputNumber();
                std::cout << CLEAR_LINE << LINE_UP << CLEAR_LINE <<  GO_TO_BEGINNING_OF_LINE;
            }while(minimumAge == 0);

            do{
                std::cout << "Stream Type (PRIVATE or PUBLIC): ";
                std::cin >> type;
                std::cout << CLEAR_LINE << LINE_UP << CLEAR_LINE <<  GO_TO_BEGINNING_OF_LINE;
            }while (type == StreamType::INVALID);

            if(type == StreamType::PRIVATE){
                do{
                    std::cout << "Max Number of Viewers: ";
                    maxNumOfViewers = inputNumber();
                    std::cout << CLEAR_LINE << LINE_UP << CLEAR_LINE <<  GO_TO_BEGINNING_OF_LINE;
                }while(maxNumOfViewers == 0);
            }

            do{
                std::cout << "Stream Genre (GAMING, TALKSHOW, MUSIC, COOKING) : ";
                std::cin >> genre;
                std::cout << CLEAR_LINE << LINE_UP << CLEAR_LINE <<  GO_TO_BEGINNING_OF_LINE;
            }while (genre == StreamGenre::INVALID);



            std::cout << CLEAR_SCREEN << GO_TO_TOP;
            pageOutput();
            std::cout << "Are you sure you wish your stream parameters to be like this: " << std::endl;
            std::cout << "Title -> " << title << std::endl;
            std::cout << "Language -> " << language << std::endl;
            std::cout << "Minimum Age -> " << minimumAge << std::endl;
            std::cout << "Stream Type -> " << type << std::endl;
            std::cout << "Genre -> " << genre << std::endl;
            if(type == StreamType::PRIVATE) std::cout << "Max number of viewers -> " << maxNumOfViewers << std::endl;
            std::cout << "\n 0 to accept and go back to the menu" << std::endl;
            answer = _getch_();
            if(answer== '0'){
                auto stream = uiManager.getPlatform().getStreamManager()->build(title,language,minimumAge,type,genre,thisStreamer);
                if(type == StreamType::PRIVATE) std::dynamic_pointer_cast<PrivateStream>(stream)->setMaxNumViewers(maxNumOfViewers);
            }
        }while (answer != '0' && answer != *ESC);
    }

}

void StreamerView::seeStreamStatistics() {
    std::shared_ptr<Streamer> currentStreamer;
    std::shared_ptr<Stream> currentStream;

    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();

    try{
        currentStreamer = uiManager.getPlatform().getStreamerManager()->get(uiManager.getCurrentSession().getNickname());
        currentStream = uiManager.getPlatform().getStreamManager()->get(currentStreamer->getCurrentStreamID());
    }catch(std::exception& exception){
        std::cerr << exception.what() << std::endl;
        _getch_();
        return;
    }

    std::cout << "\nCurrent number of viewers -> " << currentStream->getNumOfViewers() << std::endl;
    std::cout << "Number of Likes -> " << currentStream->getVotes().first << std::endl;
    std::cout << "Number of Dislikes -> " << currentStream->getVotes().second << std::endl;
    if(currentStream->getStreamType() == StreamType::PRIVATE){
        auto currentStreamPrivate = std::dynamic_pointer_cast<PrivateStream>(currentStream);
        std::cout << "Comments:\n" << std::endl;
        for(const auto& elem: currentStreamPrivate->getComments()){
            std::cout << elem.first << ": " << elem.second << std::endl;
        }
    }
    std::cout << "Press any key to leave!" << std::endl;
    _getch_();
}

void StreamerView::oldEnoughViewerLB() {
    std::shared_ptr<Streamer> currentStreamer;
    std::shared_ptr<Stream> currentStream;

    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();

    try{
        currentStreamer = uiManager.getPlatform().getStreamerManager()->get(uiManager.getCurrentSession().getNickname());
        currentStream = uiManager.getPlatform().getStreamManager()->get(currentStreamer->getCurrentStreamID());
    }catch(std::exception& exception){
        std::cerr << exception.what() << std::endl;
        _getch_();
        return;
    }

    auto oldEnoughViewerLB = uiManager.getPlatform().getLeaderboardManager()->filterViewerByAge(currentStream->getMinAge());
    std::cout << oldEnoughViewerLB;
    std::cout << "Press any key to leave!" << std::endl;
    _getch_();
}

void StreamerView::addViewersToWhitelist() {
    std::string nicknameToAdd;
    std::shared_ptr<Streamer> currentStreamer;
    std::shared_ptr<Stream> currentStream;

    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();

    try{
        currentStreamer = uiManager.getPlatform().getStreamerManager()->get(uiManager.getCurrentSession().getNickname());
        currentStream = uiManager.getPlatform().getStreamManager()->get(currentStreamer->getCurrentStreamID());
    }catch(std::exception& exception){
        std::cerr << exception.what() << std::endl;
        _getch_();
        return;
    }
    if(currentStream->getStreamType() == StreamType::PRIVATE){
        std::cout << "What nickname do you wish to add to the whitelist? ";
        getlineCIN(nicknameToAdd);
        auto currentStreamPrivate = std::dynamic_pointer_cast<PrivateStream>(currentStream);
        try{
            auto viewer = uiManager.getPlatform().getViewerManager()->get(nicknameToAdd);
            if(currentStreamPrivate->addToWhitelist(viewer)){
                std::cout << "Viewer successfully added to the whitelist!" << std::endl;
            }
            _getch_();
        } catch (std::exception& exception) {
            std::cerr << exception.what();
            _getch_();
        }
    }else{
        std::cerr << "\nThe current stream is Public! There's no whitelist!" << std::endl;
        _getch_();
    }

}

void StreamerView::finishCurrentStream() {
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();
    auto currentStreamer = uiManager.getPlatform().getStreamerManager()->get(uiManager.getCurrentSession().getNickname());
    try{
        uiManager.getPlatform().getStreamerManager()->endStream(currentStreamer);
    } catch (std::exception& exception) {
        std::cerr << exception.what();
        _getch_();
    }
}

void StreamerView::checkPastStreams() {
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();
    auto currentStreamer = uiManager.getPlatform().getStreamerManager()->get(uiManager.getCurrentSession().getNickname());
    std::vector<std::shared_ptr<Stream>> finishedStreams;
    for(const auto& elem: currentStreamer->getPreviousStreamsIDs()){
        finishedStreams.push_back(uiManager.getPlatform().getStreamManager()->get(elem));
    }
    std::cout << Leaderboard<std::shared_ptr<Stream>>(finishedStreams) << std::endl;
    _getch_();
}

bool StreamerView::accountSettings() {
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();
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
                    auto streamer = uiManager.getPlatform().getStreamerManager()->get(uiManager.getCurrentSession().getCurrentUser()->getNickname());
                    if(streamer->isStreaming()){
                        finishCurrentStream();
                    }
                    return true;
                } else break;
            }
        }
    }while (answer != '0' && answer != *ESC);
    return false;
}

void StreamerView::merchSystem() {
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();
    char answer;
    std::cout << "\n 1 - Set up merch" << std::endl;
    std::cout << "\n 2 - Handle next order" << std::endl;
    std::cout << "\n 0 - Go to main menu" << std::endl;

    auto streamer = uiManager.getPlatform().getStreamerManager()->get(uiManager.getCurrentSession().getNickname());

    do{
        answer = _getch_();
        switch (answer) {
            case '1':{
                streamer->setUpMerch(uiManager.getPlatform().getAdminManager()->getMerchLimit());
                std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP
                          << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;
                std::cout << "Merch setup done!";
                answer = '0';
                _getch_();
                break;}
            case '2': {
                std::cout << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP << CLEAR_LINE << LINE_UP
                          << CLEAR_LINE << LINE_UP << GO_TO_BEGINNING_OF_LINE;

                if(streamer->getStreamerMerch().getLimit() == 0) std::cout << "You might not have the merch system set up (can't take orders yet)!" << std::endl;
                else{
                    try{
                        auto merch = streamer->processNextOrder();
                        std::cout << "The order:\n\nBuyer: " << merch.getBuyer() << "\nNumber of Products: " << merch.getQuantity() <<"\n\n Is now processed!";
                    } catch (std::exception &e) {
                        std::cerr << e.what();
                    }
                }
                _getch_();
                answer = '0';
                break;
            }
        }
    }while (answer != '0' && answer != *ESC);
}
