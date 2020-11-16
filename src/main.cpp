#include <iostream>
#include "./ui/initialPage/initialPage.h"
#include "./model/stream/stream.h"
#include "./model/user/user.h"
#include "./model/streamZ/streamZ.h"
#include "./ui/ui_manager.h"

//==================================================

#ifdef _WIN32
#define MY_UNICODE
#include <windows.h>
#include <wincon.h>

#ifndef DISABLE_NEWLINE_AUTO_RETURN
#define DISABLE_NEWLINE_AUTO_RETURN 0x0008
#endif
#ifndef ENABLE_VIRTUAL_TERMINAL_INPUT
#define ENABLE_VIRTUAL_TERMINAL_INPUT 0x0200
#endif
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

/**
   Sets up the console in order to accept ANSI codes. Code from Microsoft Docs.
   https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#example-of-enabling-virtual-terminal-processing

   @return True if it set up the ANSI codes correctly, false otherwise.
 */
bool setUpConsole() {
	// Set output mode to handle virtual terminal sequences
	if (!SetConsoleCP(CP_UTF8) || !SetConsoleOutputCP(CP_UTF8)) {
		return (false);
	}
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hIn == INVALID_HANDLE_VALUE || hOut == INVALID_HANDLE_VALUE) {
		return (false);
	}
	DWORD dwOriginalInMode = 0;
	DWORD dwOriginalOutMode = 0;
	if (!GetConsoleMode(hIn, &dwOriginalInMode)) {
		return (false);
	}
	if (!GetConsoleMode(hOut, &dwOriginalOutMode)) {
		return (false);
	}
	DWORD dwInMode = dwOriginalInMode | ENABLE_VIRTUAL_TERMINAL_INPUT;
	if (!SetConsoleMode(hIn, dwInMode)) {
		// Failed to set VT input mode, can't do anything here.
		return (false);
	}
	DWORD dwOutMode = dwOriginalOutMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
	if (!SetConsoleMode(hOut, dwOutMode)) {
		// we failed to set both modes, try to step down mode gracefully.
		dwOutMode = dwOriginalOutMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		if (!SetConsoleMode(hOut, dwOutMode)) {
			// Failed to set any VT mode, can't do anything here.
			return (false);
		}
	}
	return (true);
}

#endif //_WIN32


int main() {
    // Sets up Windows Console to accept Ansi Escape Codes
    #ifdef MY_UNICODE
        if (!setUpConsole()) {
		    std::cerr << "\n Something went wrong setting up the console. The display is compromised, please check the code." << std::endl;
		    std::cout << "\n Press any key to leave.";
		    if (char pressedKey = (char)_getch()) {
			    return (-1);
		    }
	    }
    #endif

    StreamZ twitch = StreamZ();
        CurrentSession currentSession =  CurrentSession(twitch.getUserManager());
        UIManager twitchUI(twitch, currentSession);

    twitchUI.setCurrent(new InitialPage(twitchUI));
    twitchUI.run();
    return 0;
}
