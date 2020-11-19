//
// Created by biromiro on 15/11/20.
//

#ifndef PROJECT_AUXILIARYFUNCTIONS_H
#define PROJECT_AUXILIARYFUNCTIONS_H

#ifdef _WIN32
#define CONIO_GETCH
#include <conio.h>
#endif

#ifdef __linux__
#define TERMIOS_GETCH
#include <termios.h>
#endif

#include <cstdio>
#include <iostream>

// COLOR ANSI CODES
constexpr const char *CLEAR_SCREEN = "\x1b[2J";
constexpr const char *LINE_UP = "\033[A";
constexpr const char *CLEAR_LINE = "\x1b[2K";
constexpr const char *GO_TO_BEGINNING_OF_LINE = "\x1b[0G";
constexpr const char *RESET = "\x1b[0m";
constexpr const char *HIDE_CURSOR = "\x1b[?25l";
constexpr const char *SHOW_CURSOR = "\x1b[?25h";
constexpr const char *GO_TO_TOP = "\033[1;1H";
constexpr const char *ESC = "\033";
constexpr const int WIDTH = 15;

#ifdef TERMIOS_GETCH
void initTermios(int echo);
void resetTermios();
char getch_(int echo);
char getch();
#endif
bool is_number(const std::string& s);
unsigned int inputNumber();
void getlineCIN(std::string& s);
std::string shrinkToColumnSize(std::string value);


#endif //PROJECT_AUXILIARYFUNCTIONS_H
