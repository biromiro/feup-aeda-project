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
        std::cout << "0 - Go back" << std::endl;
        answer = getch();
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
    char answer = getch();
    if(answer == '1'){
        std::cout << uiManager.getPlatform().getLeaderboardManager()->top10StreamsBy(SortStream::VIEWS) << std::endl;
    }else if(answer == '2'){
        std::cout << uiManager.getPlatform().getLeaderboardManager()->top10StreamsBy(SortStream::LIKES) << std::endl;
    }
    getch();
}

void LeaderboardPage::showStreams() {
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();
    std::cout <<  "Do you wish to filter out the streams? (Y to accept)" << std::endl;
    char answer = getch();
    std::vector<std::shared_ptr<Stream>> streamVec;
    if(answer == 'y' || answer == 'Y'){
        std::cout << CLEAR_LINE << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
        std::cout << "What filter do you wish to apply?" << std::endl;
        std::cout << "1 - LANGUAGE" << std::endl;
        std::cout << "2 - GENRE" << std::endl;
        std::cout << "3 - AGE" << std::endl;
        std::cout << "4 - DATE" << std::endl;
        std::cout << "5 - TYPE" << std::endl;
        std::cout << "0 - CANCEL" << std::endl;
        answer = getch();
        std::cout << CLEAR_SCREEN << GO_TO_TOP;
        pageOutput();
        switch (answer) {
            case '1':{
                StreamLanguage language = StreamLanguage::INVALID;
                do {
                    std::cout << "What language?" << std::endl;
                    std::cin >> language;
                    std::cout << CLEAR_LINE << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
                } while (language == StreamLanguage::INVALID);
                streamVec = uiManager.getPlatform().getLeaderboardManager()->filterStreamByLanguage(language).get();
                break;
            }case '2': {
                StreamGenre genre = StreamGenre::INVALID;
                do {
                    std::cout << "What genre?" << std::endl;
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
                        std::cout << "That birth date is not valid!";
                        getch();
                        std::cout << CLEAR_LINE << LINE_UP << CLEAR_LINE <<  GO_TO_BEGINNING_OF_LINE;
                        continue;
                    }else break;
                }while (true);
                streamVec = uiManager.getPlatform().getLeaderboardManager()->filterStreamByDate(date).get();
                break;
            }case '5':{
                StreamType type = StreamType::INVALID;
                do{
                    std::cout << "What type?" << std::endl;
                    std::cin >> type;
                    std::cout << CLEAR_LINE << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;

                }while (type == StreamType::INVALID);
                streamVec = uiManager.getPlatform().getLeaderboardManager()->filterStreamByType(type).get();
                break;
            }
        }
    }else streamVec = uiManager.getPlatform().getLeaderboardManager()->sortStreams().get();

    do{
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
        answer = getch();
        std::cout << CLEAR_SCREEN << GO_TO_TOP;
        pageOutput();
        switch (answer) {
            case '1':{
                std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamsBy(SortStream::LANGUAGE,streamVec);
                getch();
                answer = '0';
                break;
            }case '2':{
                std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamsBy(SortStream::GENRE,streamVec);
                getch();
                answer = '0';
                break;
            }case '3':{
                std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamsBy(SortStream::MINIMUM_AGE,streamVec);
                getch();
                answer = '0';
                break;
            }case '4':{
                std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamsBy(SortStream::VIEWS,streamVec);
                getch();
                answer = '0';
                break;
            }case '5':{
                std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamsBy(SortStream::LIKES,streamVec);
                getch();
                answer = '0';
                break;
            }case '6':{
                std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamsBy(SortStream::DATE,streamVec);
                getch();
                answer = '0';
                break;
            }case '7':{
                std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamsBy(SortStream::TYPE,streamVec);
                getch();
                answer = '0';
                break;
            }
        }
    }while(answer != '0');
}

void LeaderboardPage::showUsers() {

    char answer, sortAnswer;
    do{
        std::cout << CLEAR_SCREEN << GO_TO_TOP;
        pageOutput();
        std::cout <<  "Who do you wish to sort? (Y to accept)" << std::endl;
        std::cout << "1 - VIEWERS" << std::endl;
        std::cout << "2 - STREAMERS" << std::endl;
        std::cout << "3 - ALL USERS" << std::endl;
        std::cout << "0 - Go back" << std::endl;
        answer = getch();
        if(answer == '0') return;
    }while (!(answer == 1 || answer == 2 || answer ==3));
    do{
        std::cout << CLEAR_SCREEN << GO_TO_TOP;
        pageOutput();
        switch (answer) {
            case '1': {
                std::cout << "What sort do you wish to apply?" << std::endl;
                std::cout << "1 - NAME" << std::endl;
                std::cout << "2 - NICKNAME" << std::endl;
                std::cout << "3 - BIRTHDATE" << std::endl;
                std::cout << "4 - JOINDATE" << std::endl;
                std::cout << "5 - WATCHING STREAM" << std::endl;
                std::cout << "6 - NUM OF STREAMS WATCHED" << std::endl;
                std::cout << "0 - Leave to main menu" << std::endl;
                sortAnswer = getch();
                std::cout << CLEAR_SCREEN << GO_TO_TOP;
                pageOutput();
                switch (sortAnswer) {
                    case '1': {
                        std::cout << uiManager.getPlatform().getLeaderboardManager()->sortViewerBy(SortViewer::NAME);
                        getch();
                        answer = '0';
                        break;
                    }
                    case '2': {
                        std::cout
                                << uiManager.getPlatform().getLeaderboardManager()->sortViewerBy(SortViewer::NICKNAME);
                        getch();
                        answer = '0';
                        break;
                    }
                    case '3': {
                        std::cout
                                << uiManager.getPlatform().getLeaderboardManager()->sortViewerBy(SortViewer::BIRTHDATE);
                        getch();
                        answer = '0';
                        break;
                    }
                    case '4': {
                        std::cout
                                << uiManager.getPlatform().getLeaderboardManager()->sortViewerBy(SortViewer::JOINDATE);
                        getch();
                        answer = '0';
                        break;
                    }
                    case '5': {
                        std::cout << uiManager.getPlatform().getLeaderboardManager()->sortViewerBy(
                                SortViewer::WATCHING_STREAM);
                        getch();
                        answer = '0';
                        break;
                    }
                    case '6': {
                        std::cout << uiManager.getPlatform().getLeaderboardManager()->sortViewerBy(
                                SortViewer::NUM_OF_WATCHED_STREAMS);
                        getch();
                        answer = '0';
                        break;
                    }
                }
                break;
            }case '2': {
                std::cout << "What sort do you wish to apply?" << std::endl;
                std::cout << "1 - NAME" << std::endl;
                std::cout << "2 - NICKNAME" << std::endl;
                std::cout << "3 - BIRTHDATE" << std::endl;
                std::cout << "4 - JOINDATE" << std::endl;
                std::cout << "5 - VIEWCOUNT" << std::endl;
                std::cout << "6 - STREAMING" << std::endl;
                std::cout << "6 - NUM OF FOLLOWERS" << std::endl;
                std::cout << "0 - Leave to main menu" << std::endl;
                sortAnswer = getch();
                std::cout << CLEAR_SCREEN << GO_TO_TOP;
                pageOutput();
                switch (sortAnswer) {
                    case '1': {
                        std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamerBy(SortStreamer::NAME);
                        getch();
                        answer = '0';
                        break;
                    }
                    case '2': {
                        std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamerBy(SortStreamer::NICKNAME);
                        getch();
                        answer = '0';
                        break;
                    }
                    case '3': {
                        std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamerBy(SortStreamer::BIRTHDATE);
                        getch();
                        answer = '0';
                        break;
                    }
                    case '4': {
                        std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamerBy(SortStreamer::JOINDATE);
                        getch();
                        answer = '0';
                        break;
                    }
                    case '5': {
                        std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamerBy(SortStreamer::VIEWCOUNT);
                        getch();
                        answer = '0';
                        break;
                    }
                    case '6': {
                        std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamerBy(SortStreamer::STREAMING);
                        getch();
                        answer = '0';
                        break;
                    }case '7':{
                        std::cout << uiManager.getPlatform().getLeaderboardManager()->sortStreamerBy(SortStreamer::NUM_FOLLOWERS);
                        getch();
                        answer = '0';
                        break;
                    }
                }
                break;
            }case '3': {
                std::cout << "What sort do you wish to apply?" << std::endl;
                std::cout << "1 - NAME" << std::endl;
                std::cout << "2 - NICKNAME" << std::endl;
                std::cout << "3 - BIRTHDATE" << std::endl;
                std::cout << "4 - JOINDATE" << std::endl;
                std::cout << "5 - USERTYPE" << std::endl;
                std::cout << "0 - Leave to main menu" << std::endl;
                sortAnswer = getch();
                std::cout << CLEAR_SCREEN << GO_TO_TOP;
                pageOutput();
                switch (sortAnswer) {
                    case '1': {
                        std::cout << uiManager.getPlatform().getLeaderboardManager()->sortUserBy(SortUser::NAME);
                        getch();
                        answer = '0';
                        break;
                    }
                    case '2': {
                        std::cout << uiManager.getPlatform().getLeaderboardManager()->sortUserBy(SortUser::NICKNAME);
                        getch();
                        answer = '0';
                        break;
                    }
                    case '3': {
                        std::cout << uiManager.getPlatform().getLeaderboardManager()->sortUserBy(SortUser::BIRTHDATE);
                        getch();
                        answer = '0';
                        break;
                    }
                    case '4': {
                        std::cout << uiManager.getPlatform().getLeaderboardManager()->sortUserBy(SortUser::JOINDATE);
                        getch();
                        answer = '0';
                        break;
                    }
                    case '5': {
                        std::cout << uiManager.getPlatform().getLeaderboardManager()->sortUserBy(SortUser::USERTYPE);
                        getch();
                        answer = '0';
                        break;
                    }
                }
            }
                break;
        }
    }while(answer != '0');
}
