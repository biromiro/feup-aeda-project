//
// Created by biromiro on 15/11/20.
//

#ifndef PROJECT_AUXILIARYFUNCTIONS_H
#define PROJECT_AUXILIARYFUNCTIONS_H

#include <termios.h>
#include <stdio.h>

// COLOR ANSI CODES
constexpr const char *CLEAR_SCREEN = "\x1b[2J";
constexpr const char *LINE_UP = "\033[A";
constexpr const char *CLEAR_LINE = "\x1b[2K";
constexpr const char *BG_BLACK = "\033[47;30m";
constexpr const char *RED = "\x1b[0;31m";
constexpr const char *GREEN = "\x1b[0;32m";
constexpr const char *YELLOW = "\x1b[0;33m";
constexpr const char *BLUE = "\x1b[0;34m";
constexpr const char *CYAN = "\x1b[0;36m";
constexpr const char *RESET = "\x1b[0m";
constexpr const char *HIDE_CURSOR = "\x1b[?25l";
constexpr const char *SHOW_CURSOR = "\x1b[?25h";

void initTermios(int echo);
void resetTermios(void);
char getch_(int echo);
char getch(void);

#endif //PROJECT_AUXILIARYFUNCTIONS_H
