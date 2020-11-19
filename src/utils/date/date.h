//
// Created by biromiro on 18/10/20.
//

#ifndef PROJECT_DATE_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>


class Date{
public:
    Date();
    Date(unsigned int y, unsigned int m, unsigned int d);
    Date(unsigned int y, unsigned int m, unsigned int d, unsigned int h, unsigned int min, unsigned int sec);
    explicit Date(const std::string& yearMonthDay);  //yearMonthDay must be in format yyyy/MM/dd
    void setYear(unsigned int y);
    void setMonth(unsigned int m);
    void setDay(unsigned int d);
    void setHours(unsigned int hours);
    void setMinutes(unsigned int minutes);
    void setSeconds(unsigned int seconds);
    void setDate(unsigned int y, unsigned int m, unsigned int d);
    [[nodiscard]] unsigned int getYear() const;
    [[nodiscard]] unsigned int getMonth() const;
    [[nodiscard]] unsigned int getDay() const;
    [[nodiscard]] unsigned int getHours() const;
    [[nodiscard]] unsigned int getMinutes() const;
    [[nodiscard]] unsigned int getSeconds() const;
    [[nodiscard]] std::string getDate() const;
    void show() const;
    [[nodiscard]] unsigned int totalNumOfDays() const;
    [[nodiscard]] bool isValid() const;
    [[nodiscard]] bool isEqualTo(const Date &date) const;

    [[nodiscard]] bool isAfter(const Date &date) const;
    [[nodiscard]] bool isBefore(const Date &date) const;
    friend std::ostream &operator<<(std::ostream &os, const Date &date);
    friend std::istream &operator>>(std::istream &os, Date &date);
    bool operator==(const Date &rhs) const;
    bool operator!=(const Date &rhs) const;
    bool operator<(const Date &rhs) const;
    bool operator>(const Date &rhs) const;
    bool operator<=(const Date &rhs) const;
    bool operator>=(const Date &rhs) const;
private:
    unsigned int year{};
    unsigned int month{};
    unsigned int day{};
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;
};

Date daysToDate(unsigned int days);
Date timeElapsed(const Date& d1, const Date& d2);
unsigned int numberOfDays(unsigned int year, unsigned int month);
bool isLeap(unsigned int y);

#define PROJECT_DATE_H

#endif //PROJECT_DATE_H
