//
// Created by biromiro on 18/10/20.
//

#ifndef PROJECT_DATE_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

time_t ttime = time(nullptr);
tm *local_time = localtime(&ttime);

class Date{
public:
    Date();
    Date(unsigned int y, unsigned int m, unsigned int d);
    explicit Date(const std::string& yearMonthDay);  //yearMonthDay must be in format yyyy/MM/dd
    void setYear(unsigned int y);
    void setMonth(unsigned int m);
    void setDay(unsigned int d);
    void setDate(unsigned int y, unsigned int m, unsigned int d);
    unsigned int getYear() const;
    unsigned int getMonth() const;
    unsigned int getDay() const;
    std::string getDate() const;
    void show() const;
    static bool isLeap(unsigned int y) ;
    static unsigned int numberOfDays(unsigned int year, unsigned int month) ;
    bool isValid() const;
    bool isEqualTo(const Date &date) const;
    bool isNotEqualTo(const Date &date) const;
    bool operator<(const Date &rhs) const;
    bool operator>(const Date &rhs) const;
    bool operator<=(const Date &rhs) const;
    bool operator>=(const Date &rhs) const;
    bool isAfter(const Date &date) const;
    bool isBefore(const Date &date) const;
    friend std::ostream &operator<<(std::ostream &os, const Date &date);
    bool operator==(const Date &rhs) const;
    bool operator!=(const Date &rhs) const;

private:
    unsigned int year{};
    unsigned int month{};
    unsigned int day{};
};

#define PROJECT_DATE_H

#endif //PROJECT_DATE_H
