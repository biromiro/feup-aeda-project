//
// Created by biromiro on 15/11/20.
//

#ifndef PROJECT_LEADERBOARDPAGE_H
#define PROJECT_LEADERBOARDPAGE_H

#include "../ui_manager.h"
#include "../initialPage/initialPage.h"

/**
 * @file leaderboardPage.cpp
 *
 * @brief Deals with the Leaderboard Page in the UI
 *
 * @ingroup UI
 */

/**
 * Implementation of the Leaderboard's Page in the UI
 *
 * Allows any user to access the leaderboards, to filter and sort any information on the platform
 */
class LeaderboardPage : public UI{
public:
    /**
     * Leaderboard Page's default constructor
     *
     * @param uiManager the manager of the current UI
     */
    explicit LeaderboardPage(UIManager& uiManager);

    /**
     * Runs the Leaderboard Prompt
     */
    void run() override;
private:
    UIManager& uiManager;

    /**
     * Prints the header of the UI page to the screen
     */
    static void pageOutput() ;

    /**
     * Shows the Top10 of streams given a sorting option
     */
    void top10s();

    /**
     * Prints the available streams, according to a optional filter and sort
     */
    void showStreams();

    /**
     * Prints the available user, according to a optional sort
     */
    void showUsers();

    /**
     * Filters the streams to output
     */
    void filterStreams(std::vector<std::shared_ptr<Stream>>& streamVec);

    /**
     * Sorts the viewers given an option
     */
    void sortViewers();

    /**
     * Sorts the streamers given an option
     */
    void sortStreamers();

    /**
     * Sorts the users given an option
     */
    void sortUsers();

    void showDonations();
};


#endif //PROJECT_LEADERBOARDPAGE_H
