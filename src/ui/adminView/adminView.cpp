//
// Created by biromiro on 15/11/20.
//

#include "adminView.h"

AdminView::AdminView(UIManager &uiManager) : uiManager(uiManager){}

void AdminView::run() {
    char answer ;
    do{
        pageOutput();
        std::cout << "\n1 - Check StreamZ statistics" << std::endl;
        std::cout << "2 - Go to leaderboards" << std::endl;
        std::cout << "3 - Check Donations" << std::endl;
        std::cout << "0 - Logout" << std::endl;
        answer = _getch_();
        switch (answer) {
            case '1':
                showStreamZStatistics();
                break;
            case '2':
                uiManager.setCurrent(new LeaderboardPage(uiManager));
                uiManager.run();
                break;
            case '3':
                showDonationsWithFilter();
                break;
            case '0':
                uiManager.getCurrentSession().logout();
                break;
            default:
                break;
        }
    }while (answer != *ESC && answer != '0');
}

void AdminView::pageOutput() {
    std::cout << "*****StreamZ*****ADMINISTRATION*****" << std::endl;
}

void AdminView::showStreamZStatistics() const {
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();

    //gets all info from the leaderboard manager

    std::cout << uiManager.getPlatform().getLeaderboardManager()->totalNumberOfStreams() << " streams were created in total." << std::endl;
    std::cout << uiManager.getPlatform().getLeaderboardManager()->meanViewsPerStreamActive() << " is the mean of views per stream." << std::endl;
    std::cout << uiManager.getPlatform().getLeaderboardManager()->meanViewsPerStreamFinished() << " is the mean of views per finished stream." << std::endl;
    std::cout << "There are " << uiManager.getPlatform().getLeaderboardManager()->totalNumberOfPrivateStreams() << " private streams up and running." << std::endl;
    std::cout << "There are " << uiManager.getPlatform().getLeaderboardManager()->totalNumberOfPublicStreams() << " public streams up and running." << std::endl;
    std::cout << uiManager.getPlatform().getLeaderboardManager()->mostCommonLanguage() << " is the most common language among streams." << std::endl;
    std::cout << uiManager.getPlatform().getLeaderboardManager()->mostCommonType() << " is the most common type of stream." << std::endl;
    std::cout << uiManager.getPlatform().getLeaderboardManager()->mostViewsStreamer() << " is the streamer with the most total views." << std::endl;

    _getch_();
}

void AdminView::showDonationsWithFilter() const {
    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();

    unsigned int lowerBound, upperBound;
    float ammount;

    do{
        std::cout << "Please select the lower bound of the donation to show (1-5): ";
        lowerBound = inputNumber();
        std::cout << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
    }while (lowerBound < 1 || lowerBound > 5);

    do{
        std::cout << "Please select the upper bound of the donation to show (1-5): ";
        upperBound = inputNumber();
        std::cout << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
    }while (upperBound < lowerBound || upperBound > 5);

    do{
        std::cout << "Please select the minimum donation value to show: ";
        ammount = inputFloat();
        std::cout << LINE_UP << CLEAR_LINE << GO_TO_BEGINNING_OF_LINE;
    }while (ammount <= 0);

    std::cout << CLEAR_SCREEN << GO_TO_TOP;
    pageOutput();

    auto lower = static_cast<streamerWorkRating>(lowerBound-1);
    auto upper = static_cast<streamerWorkRating>(upperBound-1);
    std::cout << uiManager.getPlatform().getLeaderboardManager()->getDonationsByAvalInterval(lower,upper,ammount);

    std::cout << "Press any key to go the main menu";

    _getch_();
}
