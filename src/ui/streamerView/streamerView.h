//
// Created by biromiro on 15/11/20.
//

#ifndef PROJECT_STREAMERVIEW_H
#define PROJECT_STREAMERVIEW_H

#include "../ui_manager.h"
#include "../initialPage/initialPage.h"

class StreamerView : public UI{
public:
    explicit StreamerView(UIManager& uiManager);
    void run() override;
private:
    UIManager& uiManager;
    void pageOutput() const;
    void startStream();
    void seeStreamStatistics();
    void oldEnoughViewerLB();
    void addViewersToWhitelist();
    void finishCurrentStream();
    void checkPastStreams();
};

#endif //PROJECT_STREAMERVIEW_H
