//
// Created by biromiro on 15/11/20.
//

#ifndef PROJECT_STREAMVIEW_H
#define PROJECT_STREAMVIEW_H

#include "../ui_manager.h"
#include "../initialPage/initialPage.h"

class StreamView : public UI{
public:
    explicit StreamView(UIManager& uiManager);
    void run() override;
private:
    UIManager& uiManager;
    void pageOutput() const;
};

#endif //PROJECT_STREAMVIEW_H
