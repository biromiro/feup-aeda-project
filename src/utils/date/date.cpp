//
// Created by biromiro on 18/10/20.
//

#include "date.h"

time_t ttime = time(nullptr);
tm *local_time = localtime(&ttime);

Date::Date(){
    year = 1900 + local_time->tm_year;
    month = 1 + local_time->tm_mon;
    day = local_time->tm_mday;
}

Date::Date(unsigned int y, unsigned int m, unsigned int d){
    year = y;
    month = m;
    day = d;
}

Date::Date(const std::string& yearMonthDay){
    std::istringstream inp(yearMonthDay);
    char separator;
    inp >>  year >> separator >> month >> separator >> year;
}

void Date::setYear(unsigned int y){
    year = y;
}

void Date::setMonth(unsigned int m){
    month = m;
}

void Date::setDay(unsigned int d){
    day = d;
}

void Date::setDate(unsigned int y, unsigned int m, unsigned int d){
    year = y;
    month = m;
    day = d;
}

unsigned int Date::getYear() const {
    return year;
}

unsigned int Date::getMonth() const {
    return month;
}

unsigned int Date::getDay() const {
    return day;
}

std::string Date::getDate() const {
    std::string date,y,m,d;
    if(std::to_string(year).size()<=4){
        y = std::string(4-std::to_string(year).size(),'0') + std::to_string(year);
    }
    if(std::to_string(month).size()<=2){
        m = std::string(2-std::to_string(month).size(),'0') + std::to_string(month);
    }
    if(std::to_string(day).size()<=2){
        d = std::string(2-std::to_string(day).size(),'0') + std::to_string(day);
    }
    date = y + "/" + m + "/" + d;
    return date;
}

void Date::show() const {
    std::cout << std::setw(4) << std::setfill('0')  << year << "/" << std::setw(2) << std::setfill('0') <<month << "/" << std::setw(2) << std::setfill('0') << day;
}

bool Date::isLeap (unsigned int y) {
    if (y % 400 == 0) return true;
    else return ((y % 4 == 0) && (y % 100 != 0));
}

unsigned int Date::numberOfDays(unsigned int y, unsigned int m) {
    if (m == 2){
        if (isLeap(y)){return 29;}
        else {return 28;}
    } else if (((m % 2 == 1) && (m <8)) || ((m % 2 == 0) && (m >= 8))){return 31;}
    else {return 30;}
}

bool Date::isValid() const {
    unsigned int days = numberOfDays(year,month);
    if(day<0 || day>days)
        return false;
    else return !(month < 0 || month > 12) && year >= 0;
}

bool Date::isEqualTo(const Date &date) const {
    if(date.getDate() == getDate()){
        return true;
    }
    return false;
}

bool Date::isNotEqualTo(const Date &date) const {
    return !(isEqualTo(date));
}

bool Date::isAfter(const Date &date) const {
    if (isEqualTo(date)) return false;
    else if (date.getYear() < getYear())
        return true;
    else if (date.getMonth() < getMonth() && date.getYear() == getYear())
        return true;
    else return date.getDay() <= getDay() && date.getMonth() == getMonth() && date.getYear() == getYear();
}

bool Date::isBefore(const Date &date) const {
    if(isEqualTo(date)) return false;
    return !(isAfter(date));
}

std::ostream &operator<<(std::ostream &os, const Date &date) {
    os << "year: " << date.year << " month: " << date.month << " day: " << date.day;
    return os;
}

bool Date::operator<(const Date &rhs) const {
    if (year < rhs.year)
        return true;
    if (rhs.year < year)
        return false;
    if (month < rhs.month)
        return true;
    if (rhs.month < month)
        return false;
    return day < rhs.day;
}

bool Date::operator>(const Date &rhs) const {
    return rhs < *this;
}

bool Date::operator<=(const Date &rhs) const {
    return !(rhs < *this);
}

bool Date::operator>=(const Date &rhs) const {
    return !(*this < rhs);
}

bool Date::operator==(const Date &rhs) const {
    return year == rhs.year &&
           month == rhs.month &&
           day == rhs.day;
}

bool Date::operator!=(const Date &rhs) const {
    return !(rhs == *this);
}