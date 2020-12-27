//
// Created by biromiro on 15/11/20.
//

#include "leaderboardPage.h"

LeaderboardPage::LeaderboardPage(UIManager &uiManager) : uiManager(uiManager){}

void LeaderboardPage::run() {
    char answer ;
    do{
        std::cout << CLEAR_SCREEN << GO_TO_TOP;
        pageOutput();
        std::cout << "\n1 - Show me the top 10's of Streams" << std::endl;
        std::cout << "2 - List all available streams with filter" << std::endl;
        std::cout << "3 - List all users in the platform with filter" << std::endl;
        std::cout << "4 - Show me all donations!" << std::endl;
        std::cout << "0 - Go back" << std::endl;
        answer = _getch_();
        switch (answer) {
            case '1':
                top10s();
                break;
            case '2':
                showStreams();
                break;
            case '3':
                showUsers();
                break;
            case '4':
                showDonations();
                break;
            default:
                break;
        }
    }while (answer != *ESC && answer != '0');
}

void LeaderboardPage::pageOutput() {
    std::cout << "*****StreamZ*****Leaderboards*****" << std::endl;
}

void LeaderboardPage::top10s() {
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();
    std::cout << "Which sorting method do you wish to apply to the TOP 10?" << std::endl;
    std::cout << "1 - VIEWS" << std::endl;
    std::cout << "2 - LIKES" << std::endl;
    char answer = _getch_();
    if(answer == '1'){
        std::cout << uiManager.getPlatform().getLeaderboardManager()->top10StreamsBy(SortStream::VIEWS) << std::endl;
    }else if(answer == '2'){
        std::cout << uiManager.getPlatform().getLeaderboardManager()->top10StreamsBy(SortStream::LIKES) << std::endl;
    }
    _getch_();
}

void LeaderboardPage::showStreams() {
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();
    std::cout << "Do you wish to filter out the streams? (Y to accept)" << std::endl;
    char answer = _getch_();
    std::vector<std::shared_ptr<Stream>> streamVec;
    if (answer == 'y' || answer == 'Y') {
        filterStreams(streamVec);
    } else streamVec = uiManager.getPlatform().getLeaderboardManager()->sortStreams().get();
    do {
        std::cout << CLEAR_SCREEN << GO_TO_TOP;
        pageOutput();
        std::cout << "What sort do you wish to apply?" << std::endl;
        std::cout << "1 - LANGUAGE" << std::endl;
        std::cout << "2 - GENRE" << std::endl;
        std::cout << "3 - AGE" << std::endl;
        std::cout << "4 - VIEWS" << std::endl;
        std::cout << "5 - LIKES" << std::endl;
        std::cout << "6 - DATE" << std::endl;
        std::cout << "7 - TYPE" << std::endl;
        std::cout << "0 - CANCEL" << std::endl;
        answer = _getch_();
        std::cout << CLEAR_SCREEN << GO_TO_TOP;
        pageOutput();
        switch (answer) {
            case '1': {
                std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamsBy(SortStream::LANGUAGE,
                                                                                            streamVec);
                _getch_();
                answer = '0';
                break;
            }
            case '2': {
                std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamsBy(SortStream::GENRE,
                                                                                            streamVec);
                _getch_();
                answer = '0';
                break;
            }
            case '3': {
                std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamsBy(SortStream::MINIMUM_AGE,
                                                                                            streamVec);
                _getch_();
                answer = '0';
                break;
            }
            case '4': {
                std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamsBy(SortStream::VIEWS,
                                                                                            streamVec);
                _getch_();
                answer = '0';
                break;
            }
            case '5': {
                std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamsBy(SortStream::LIKES,
                                                                                            streamVec);
                _getch_();
                answer = '0';
                break;
            }
            case '6': {
                std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamsBy(SortStream::DATE,
                                                                                            streamVec);
                _getch_();
                answer = '0';
                break;
            }
            case '7': {
                std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamsBy(SortStream::TYPE,
                                                                                            streamVec);
                _getch_();
                answer = '0';
                break;
            }
        }
    } while (answer != '0');
}

void LeaderboardPage::filterStreams(std::vector<std::shared_ptr<Stream>>& streamVec){
    std::cout << CLEAR_LINE << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
    std::cout << "What filter do you wish to apply?" << std::endl;
    std::cout << "1 - LANGUAGE" << std::endl;
    std::cout << "2 - GENRE" << std::endl;
    std::cout << "3 - AGE" << std::endl;
    std::cout << "4 - DATE" << std::endl;
    std::cout << "5 - TYPE" << std::endl;
    std::cout << "0 - CANCEL" << std::endl;
    char answer = _getch_();
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();
    switch (answer) {
        case '1':{
            StreamLanguage language = StreamLanguage::INVALID;
            do {
                std::cout << "What language (Abbreviation, like PT_PT for Portugal's Portuguese or EN for English) ?" << std::endl;
                std::cin >> language;
                std::cout << CLEAR_LINE << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
            } while (language == StreamLanguage::INVALID);
            streamVec = uiManager.getPlatform().getLeaderboardManager()->filterStreamByLanguage(language).get();
            break;
        }case '2': {
            StreamGenre genre = StreamGenre::INVALID;
            do {
                std::cout << "What genre (MUSIC, GAMING, COOKING, TALKSHOW)?" << std::endl;
                std::cin >> genre;
                std::cout << CLEAR_LINE << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
            } while (genre == StreamGenre::INVALID);
            streamVec = uiManager.getPlatform().getLeaderboardManager()->filterStreamByGenre(genre).get();
            break;
        }case '3':{
            unsigned int age;
            do{
                std::cout << "What age?" << std::endl;
                age = inputNumber();
                std::cout << CLEAR_LINE << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
            }while (age == 0);
            streamVec = uiManager.getPlatform().getLeaderboardManager()->filterStreamByAge(age).get();
            break;
        }case '4':{
            Date date;
            unsigned int year, month, day;
            do {
                std::cout << "What date?" << std::endl;
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
                date.setDate(year,month,day);
                if(!date.isValid()){
                    std::cerr << "That birth date is not valid!";
                    _getch_();
                    std::cout << CLEAR_LINE << LINE_UP << CLEAR_LINE <<  GO_TO_BEGINNING_OF_LINE;
                    continue;
                }else break;
            }while (true);
            streamVec = uiManager.getPlatform().getLeaderboardManager()->filterStreamByDate(date).get();
            break;
        }case '5':{
            StreamType type = StreamType::INVALID;
            do{
                std::cout << "What type (PRIVATE, PUBLIC)?" << std::endl;
                std::cin >> type;
                std::cout << CLEAR_LINE << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;

            }while (type == StreamType::INVALID);
            streamVec = uiManager.getPlatform().getLeaderboardManager()->filterStreamByType(type).get();
            break;
        }
    }
}

void LeaderboardPage::showUsers() {

    char answer;
    while (true){
        std::cout << CLEAR_SCREEN << GO_TO_TOP;
        pageOutput();
        std::cout <<  "Who do you wish to sort?" << std::endl;
        std::cout << "1 - VIEWERS" << std::endl;
        std::cout << "2 - STREAMERS" << std::endl;
        std::cout << "3 - ALL USERS" << std::endl;
        std::cout << "0 - Go back" << std::endl;
        answer = _getch_();
        if(answer == '0') return;
        if(answer == '1' || answer == '2' || answer == '3') break;
    }
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();
    switch (answer) {
        case '1': {
            sortViewers();
            break;
        }case '2': {
            sortStreamers();
            break;
        }case '3': {
            sortUsers();
            break;
        }
    }
}

void LeaderboardPage::sortViewers() {
    std::cout << "What sort do you wish to apply?" << std::endl;
    std::cout << "1 - NAME" << std::endl;
    std::cout << "2 - NICKNAME" << std::endl;
    std::cout << "3 - BIRTHDATE" << std::endl;
    std::cout << "4 - JOINDATE" << std::endl;
    std::cout << "5 - WATCHING STREAM" << std::endl;
    std::cout << "6 - NUM OF STREAMS WATCHED" << std::endl;
    std::cout << "0 - Leave to main menu" << std::endl;
    char sortAnswer = _getch_();
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();
    switch (sortAnswer) {
        case '1': {
            std::cout << uiManager.getPlatform().getLeaderboardManager()->sortViewerBy(SortViewer::NAME);
            _getch_();
            break;
        }
        case '2': {
            std::cout
                    << uiManager.getPlatform().getLeaderboardManager()->sortViewerBy(SortViewer::NICKNAME);
            _getch_();
            break;
        }
        case '3': {
            std::cout
                    << uiManager.getPlatform().getLeaderboardManager()->sortViewerBy(SortViewer::BIRTHDATE);
            _getch_();
            break;
        }
        case '4': {
            std::cout
                    << uiManager.getPlatform().getLeaderboardManager()->sortViewerBy(SortViewer::JOINDATE);
            _getch_();
            break;
        }
        case '5': {
            std::cout << uiManager.getPlatform().getLeaderboardManager()->sortViewerBy(
                    SortViewer::WATCHING_STREAM);
            _getch_();
            break;
        }
        case '6': {
            std::cout << uiManager.getPlatform().getLeaderboardManager()->sortViewerBy(
                    SortViewer::NUM_OF_WATCHED_STREAMS);
            _getch_();
            break;
        }
    }
}

void LeaderboardPage::sortStreamers() {
    std::cout << "What sort do you wish to apply?" << std::endl;
    std::cout << "1 - NAME" << std::endl;
    std::cout << "2 - NICKNAME" << std::endl;
    std::cout << "3 - BIRTHDATE" << std::endl;
    std::cout << "4 - JOINDATE" << std::endl;
    std::cout << "5 - VIEWCOUNT" << std::endl;
    std::cout << "6 - STREAMING" << std::endl;
    std::cout << "6 - NUM OF FOLLOWERS" << std::endl;
    std::cout << "0 - Leave to main menu" << std::endl;
    char sortAnswer = _getch_();
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();
    switch (sortAnswer) {
        case '1': {
            std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamerBy(SortStreamer::NAME);
            _getch_();
            break;
        }
        case '2': {
            std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamerBy(SortStreamer::NICKNAME);
            _getch_();
            break;
        }
        case '3': {
            std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamerBy(SortStreamer::BIRTHDATE);
            _getch_();
            break;
        }
        case '4': {
            std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamerBy(SortStreamer::JOINDATE);
            _getch_();
            break;
        }
        case '5': {
            std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamerBy(SortStreamer::VIEWCOUNT);
            _getch_();
            break;
        }
        case '6': {
            std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamerBy(SortStreamer::STREAMING);
            _getch_();
            break;
        }case '7':{
            std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamerBy(SortStreamer::NUM_FOLLOWERS);
            _getch_();
            break;
        }
    }
}

void LeaderboardPage::sortUsers() {
    std::cout << "What sort do you wish to apply?" << std::endl;
    std::cout << "1 - NAME" << std::endl;
    std::cout << "2 - NICKNAME" << std::endl;
    std::cout << "3 - BIRTHDATE" << std::endl;
    std::cout << "4 - JOINDATE" << std::endl;
    std::cout << "5 - USERTYPE" << std::endl;
    std::cout << "0 - Leave to main menu" << std::endl;
    char sortAnswer = _getch_();
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();
    switch (sortAnswer) {
        case '1': {
            std::cout << uiManager.getPlatform().getLeaderboardManager()->sortUserBy(SortUser::NAME);
            _getch_();
            break;
        }
        case '2': {
            std::cout << uiManager.getPlatform().getLeaderboardManager()->sortUserBy(SortUser::NICKNAME);
            _getch_();
            break;
        }
        case '3': {
            std::cout << uiManager.getPlatform().getLeaderboardManager()->sortUserBy(SortUser::BIRTHDATE);
            _getch_();
            break;
        }
        case '4': {
            std::cout << uiManager.getPlatform().getLeaderboardManager()->sortUserBy(SortUser::JOINDATE);
            _getch_();
            break;
        }
        case '5': {
            std::cout << uiManager.getPlatform().getLeaderboardManager()->sortUserBy(SortUser::USERTYPE);
            _getch_();
            break;
        }
    }
}

void LeaderboardPage::showDonations() {
    pageOutput();
    std::cout << uiManager.getPlatform().getLeaderboardManager()->getOrderedDonations();
    std::cout << "\nPress any key to go back" << std::endl;
    _getch_();
}