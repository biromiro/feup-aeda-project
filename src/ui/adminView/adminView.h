//
// Created by biromiro on 15/11/20.
//

#ifndef PROJECT_ADMINVIEW_H
#define PROJECT_ADMINVIEW_H

#include "../ui_manager.h"
#include "../initialPage/initialPage.h"

class AdminView : public UI{
public:
    explicit AdminView(UIManager& uiManager);
    void run() override;
private:
    UIManager& uiManager;
    void pageOutput() const;
    void showStreamZStatistics() const;
};

#endif //PROJECT_ADMINVIEW_H
