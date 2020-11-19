//
// Created by biromiro on 15/11/20.
//

#ifndef PROJECT_LEADERBOARDPAGE_H
#define PROJECT_LEADERBOARDPAGE_H

#include "../ui_manager.h"
#include "../initialPage/initialPage.h"

class LeaderboardPage : public UI{
public:
    explicit LeaderboardPage(UIManager& uiManager);
    void run() override;
private:
    UIManager& uiManager;
    void pageOutput() const;
    void top10s();
    void showStreams();
    void showUsers();
};


#endif //PROJECT_LEADERBOARDPAGE_H
