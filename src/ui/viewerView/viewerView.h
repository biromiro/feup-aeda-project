//
// Created by biromiro on 15/11/20.
//

#ifndef PROJECT_VIEWERVIEW_H
#define PROJECT_VIEWERVIEW_H

#include "../ui_manager.h"
#include "../initialPage/initialPage.h"
#include "../streamView/streamView.h"

/**
 * @file viewerView.cpp
 *
 * @brief Deals with the Viewer View Page in the UI
 *
 * @ingroup UI
 */

/**
 * Implementation of the Viewer's Page in the UI
 *
 * Allows a viewer to search for availabe streams and to join one, to follow or unfollow streamers, to see the view history and to check the leaderboards
 */
class ViewerView : public UI{
public:

    /**
     * Viewer View's constructor
     *
     * @param uiManager the manager of the current UI
     */
    explicit ViewerView(UIManager& uiManager);

    /**
     * Runs the viewer View output prompt
     */
    void run() override;
private:
    UIManager& uiManager;

    /**
     * Chooses a stream to join, redirects if already in one
     */
    void chooseStream();

    /**
     * Lists the streamers which the current viewer is not following
     */
    void searchNewStreamers();

    /**
     * Lists the streamers the current viewer is following
     */
    void followingStreamers();

    /**
     * Permits the current viewer to follow a new streamer
     */
    void newStreamerActions();

    /**
     * Permits the current viewer to unfollow a streamer
     */
    void followingStreamerActions();

    /**
     * Displays all available streams
     */
    void showAvailableStreams();

    /**
     * Displays the current viewer's view history
     */
    void myViewHistory();

    /**
    * Prints the header of the UI page to the screen
    */
    void pageOutput() const;

    bool accountSettings();
};

#endif //PROJECT_VIEWERVIEW_H
