//
// Created by biromiro on 15/11/20.
//

#ifndef PROJECT_STREAMVIEW_H
#define PROJECT_STREAMVIEW_H

#include "../ui_manager.h"
#include "../initialPage/initialPage.h"

/**
 * @file streamview.cpp
 *
 * @brief Deals with the Stream View Page in the UI
 *
 * @ingroup UI
 */

/**
 * Implementation of the Stream's Page in the UI
 *
 * Allows a viewer to watch a stream, give feedback and leave the stream
 */
class StreamView : public UI{
public:

    /**
     * Stream View's constructor
     *
     * @param uiManager the manager of the current UI
     */
    explicit StreamView(UIManager& uiManager);

    /**
     * Runs the stream view display
     */
    void run() override;
private:
    UIManager& uiManager;

    /**
     * Prints the header of the UI page to the screen
     */
    void pageOutput() const;

    /**
     * Gives feedback, LIKE or DISLIKE or a comment, to the stream
     */
    void feedbackToStream();
};

#endif //PROJECT_STREAMVIEW_H
