//
// Created by biromiro on 15/11/20.
//

#ifndef PROJECT_STREAMERVIEW_H
#define PROJECT_STREAMERVIEW_H

#include "../ui_manager.h"
#include "../initialPage/initialPage.h"

/**
 * @file streamerView.cpp
 *
 * @brief Deals with the Streamer Page in the UI
 *
 * @ingroup UI
 */

/**
 * Implementation of the Streamer's Page in the UI
 *
 * Allows a streamer to start a stream, check its statistics, edit whitelist and see who's able to join, as well as finish the stream and check the leaderboards
 */
class StreamerView : public UI{
public:
    /**
     * Streamer View's constructor
     *
     * @param uiManager the manager of the current UI
     */
    explicit StreamerView(UIManager& uiManager);

    /**
     * Runs the streamer page view
     */
    void run() override;
private:
    UIManager& uiManager;

    /**
     * Prints the header of the UI page to the screen
     */
    void pageOutput() const;

    /**
     * Starts a stream and receives its parameters, if not already streaming
     */
    void startStream();

    /**
     * Checks stream statistics
     */
    void seeStreamStatistics();

    /**
     * See which viewers are old enough to join the stream
     */
    void oldEnoughViewerLB();

    /**
     * Tries to add a viewer to the whitelist (if the stream is Private)
     */
    void addViewersToWhitelist();

    /**
     * Ends the current stream
     */
    void finishCurrentStream();

    /**
     * Displays the past streams of the logged streamer
     */
    void checkPastStreams();
};

#endif //PROJECT_STREAMERVIEW_H
