//
// Created by biromiro on 15/11/20.
//

#ifndef PROJECT_VIEWERVIEW_H
#define PROJECT_VIEWERVIEW_H

#include "../ui_manager.h"
#include "../initialPage/initialPage.h"
#include "../streamView/streamView.h"

class ViewerView : public UI{
public:
    explicit ViewerView(UIManager& uiManager);
    void run() override;
private:
    void chooseStream();
    void searchNewStreamers();
    void followingStreamers();
    void newStreamerActions();
    void followingStreamerActions();
    void showAvailableStreams();
    void myViewHistory();
    UIManager& uiManager;
    void pageOutput() const;
};

#endif //PROJECT_VIEWERVIEW_H
