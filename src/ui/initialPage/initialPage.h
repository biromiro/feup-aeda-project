//
// Created by nrtc on 14/11/2020.
//

#ifndef PROJECT_INITIALPAGE_H
#define PROJECT_INITIALPAGE_H

#include "../ui_manager.h"
#include "../loginPage/loginPage.h"
#include "../registerPage/registerPage.h"

/**
 * @file initialPage.cpp
 *
 * @brief Deals with the Initial Page in the UI
 *
 * @ingroup UI
 */


/**
 * Implementation of the Initial Page Prompt in the UI
 *
 * Allows the user to access register or login pages, as well as to quit and save the app
 */
class InitialPage : public UI{
public:
    /**
     * Inital Page's constructor
     *
     * @param uiManager the manager of the current UI
     */
    explicit InitialPage(UIManager& uiManager);

    /**
     * Runs the Initial Page's prompt
     */
    void run() override;
private:

    UIManager& uiManager;

    /**
     * Prints the header of the UI page to the screen
     */
    static void pageOutput() ;
};

#endif //PROJECT_INITIALPAGE_H
