//
// Created by biromiro on 15/11/20.
//

#ifndef PROJECT_STREAMVIEW_H
#define PROJECT_STREAMVIEW_H

#include "../ui_manager.h"
#include "../initialPage/initialPage.h"

class streamView : public UI{
public:
    explicit streamView(UIManager& uiManager);
    void run() override;
private:
    UIManager& uiManager;
    void pageOutput() const;
};

#endif //PROJECT_STREAMVIEW_H
