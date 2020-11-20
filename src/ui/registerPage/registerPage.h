//
// Created by biromiro on 15/11/20.
//

#ifndef PROJECT_REGISTERPAGE_H
#define PROJECT_REGISTERPAGE_H

#include "../ui_manager.h"
#include "../initialPage/initialPage.h"

/**
 * @file registerPage.cpp
 *
 * @brief Deals with the Register Page in the UI
 *
 * @ingroup UI
 */

/**
 * Implementation of the Register's Page in the UI
 *
 * Allows a user to register as viewer or streamer, by inputing and validating its information
 */
class RegisterPage : public UI{
public:

    /**
     * Register Page's default constructor
     *
     * @param uiManager the manager of the current UI
     */
    explicit RegisterPage(UIManager& uiManager);

    /**
     * Runs the register page output
     */
    void run() override;
private:
    UIManager& uiManager;

    /**
     * Prints the header of the UI page to the screen
     */
    static void pageOutput() ;

    /**
     * Allows a streamer to register
     *
     * @return True if the registering process was successful, false otherwise
     */
    bool streamerRegister();

    /**
    * Allows a viewer to register
    *
    * @return True if the registering process was successful, false otherwise
    */
    bool viewerRegister();

    /**
     * Gets, by user input, the registering information of any user
     *
     * @param birthDate the birthDate of the user
     * @param name the name of the user
     * @param nickname the nickname of the user
     * @param password the password of the user
     */
    void getUserInfo(Date& birthDate, std::string& name, std::string& nickname, std::string& password);
};

#endif //PROJECT_REGISTERPAGE_H
