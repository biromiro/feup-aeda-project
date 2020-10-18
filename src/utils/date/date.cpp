//
// Created by biromiro on 18/10/20.
//

#include <iostream>
#include <string>

class Date{
public:
    Date();
    Date(unsigned int y, unsigned int m, unsigned int d);
    Date(std::string yearMonthDay);  //yearMonthDay must be in format yyyy/MM/dd
    void setYear(unsigned int y);
    void setMonth(unsigned int m);
    void setDay(unsigned int d);
    void setDate(unsigned int y, unsigned int m, unsigned int d);
    unsigned int getYear() const;
    unsigned int getMonth() const;
    unsigned int getDay() const;
    std::string getDate() const;
    void show() const;
    bool isLeap(int y) const;
    int numberOfDays(int year, int month) const;
    bool isValid() const;
    bool isEqualTo(const Date &date);
    bool isNotEqualTo(const Date &date);
    bool operator<(const Date &rhs) const;
    bool operator>(const Date &rhs) const;
    bool operator<=(const Date &rhs) const;
    bool operator>=(const Date &rhs) const;
    bool isAfter(const Date &date);
    bool isBefore(const Date &date);
    friend std::ostream &operator<<(std::ostream &os, const Date &date);
    bool operator==(const Date &rhs) const;
    bool operator!=(const Date &rhs) const;

private:
    unsigned int year;
    unsigned int month;
    unsigned int day;
};

