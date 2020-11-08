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
    hours = local_time->tm_hour;
    minutes = local_time->tm_min;
    seconds = local_time->tm_sec;
}

Date::Date(unsigned int y, unsigned int m, unsigned int d){
    year = y;
    month = m;
    day = d;
    hours = 0;
    minutes = 0;
    seconds = 0;
}

Date::Date(unsigned int y, unsigned int m, unsigned int d, unsigned int h, unsigned int min, unsigned int sec) {
    year = y;
    month = m;
    day = d;
    hours = h;
    minutes = min;
    seconds = sec;
}

Date::Date(const std::string& yearMonthDay){
    std::istringstream inp(yearMonthDay);
    char separator;
    inp >>  year >> separator >> month >> separator >> day;
    hours = 0;
    minutes = 0;
    seconds = 0;
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

void Date::setHours(unsigned int hours) {
    Date::hours = hours;
}

void Date::setMinutes(unsigned int minutes) {
    Date::minutes = minutes;
}

void Date::setSeconds(unsigned int seconds) {
    Date::seconds = seconds;
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

unsigned int Date::getHours() const {
    return hours;
}

unsigned int Date::getMinutes() const {
    return minutes;
}

unsigned int Date::getSeconds() const {
    return seconds;
}

std::string Date::getDate() const {
    std::string date,y,m,d,h,min,s;
    if(std::to_string(year).size()<=4){
        y = std::string(4-std::to_string(year).size(),'0') + std::to_string(year);
    }
    if(std::to_string(month).size()<=2){
        m = std::string(2-std::to_string(month).size(),'0') + std::to_string(month);
    }
    if(std::to_string(day).size()<=2){
        d = std::string(2-std::to_string(day).size(),'0') + std::to_string(day);
    }
    if(std::to_string(hours).size()<=2){
        h = std::string(4-std::to_string(hours).size(),'0') + std::to_string(hours);
    }
    if(std::to_string(minutes).size()<=2){
        min = std::string(2-std::to_string(minutes).size(),'0') + std::to_string(minutes);
    }
    if(std::to_string(seconds).size()<=2){
        s = std::string(2-std::to_string(seconds).size(),'0') + std::to_string(seconds);
    }
    date = y + "/" + m + "/" + d + ", " + h + ":" + min + ":" + s;
    return date;
}

void Date::show() const {
    std::cout << std::setw(4) << std::setfill('0')  << year << "/" << std::setw(2) << std::setfill('0') <<month << "/" << std::setw(2) << std::setfill('0') << day;
    std::cout << ", " << std::setw(2) << std::setfill('0')  << hours << ":" << std::setw(2) << std::setfill('0') <<minutes << ":" << std::setw(2) << std::setfill('0') << seconds;
}

bool isLeap (unsigned int y) {
    if (y % 400 == 0) return true;
    else return ((y % 4 == 0) && (y % 100 != 0));
}

unsigned int numberOfDays(unsigned int y, unsigned int m) {
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
    else if(date.getDay() < getDay() && date.getMonth() == getMonth() && date.getYear() == getYear())
        return true;
    else if(date.getHours() < getHours())
        return true;
    else if(date.getMinutes() < getMinutes() && date.getHours() == getHours())
        return true;
    else if(date.getSeconds() < getSeconds() && date.getMinutes() == getMinutes() && date.getHours() == getHours())
        return true;
    return false;
}

bool Date::isBefore(const Date &date) const {
    if(isEqualTo(date)) return false;
    return !(isAfter(date));
}

std::ostream &operator<<(std::ostream &os, const Date &date) {
    std::stringstream ss;
    ss << std::right << std::setfill('0') << std::setw(4) << date.year << "/" << std::setw(2) << date.month << "/" << std::setw(2) << date.day << std::setfill(' ');
    std::string s = ss.str();
    os << s;
    return os;
}

std::istream &operator>>(std::istream &is, Date &date) {
    std::string str;
    char temp;
    is >> str;
    std::istringstream ss(str);
    ss >> date.year >> temp >> date.month >> temp >> date.day;
    return is;
}


unsigned int Date::totalNumOfDays() const {
    unsigned int years = getYear(), months = getMonth(), totalDays = getDay();
    for(int y=1; y<years; ++y){
        for(int m=1; m<=12; ++m){
            totalDays += numberOfDays(y,m);
        }
    }
    for(int m=1; m<months; ++m){
        totalDays += numberOfDays(getYear(),m);
    }
    return totalDays;
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
    if (day < rhs.day)
        return true;
    if (rhs.day < day)
        return false;
    if (hours < rhs.hours)
        return true;
    if (rhs.hours < hours)
        return false;
    if (minutes < rhs.minutes)
        return true;
    if (rhs.minutes < minutes)
        return false;
    return seconds < rhs.seconds;
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
           day == rhs.day &&
           hours == rhs.hours &&
           minutes == rhs.minutes &&
           seconds == rhs.seconds;
}

bool Date::operator!=(const Date &rhs) const {
    return !(rhs == *this);
}

Date daysToDate(unsigned int totalDays) {
    Date result(0,1,1);
    unsigned int lastMonthDays = numberOfDays(result.getYear(),result.getMonth());
    while(totalDays>=lastMonthDays){
        totalDays-=lastMonthDays;
        if(result.getMonth() == 12)
            result.setYear(result.getYear()+1);

        result.setMonth(result.getMonth()%12 + 1);
        lastMonthDays = numberOfDays(result.getYear(),result.getMonth());;
    }
    result.setDay(totalDays);
    return result;
}

Date timeElapsed(const Date& d1, const Date& d2){
    if(d1 < d2){
        return timeElapsed(d2,d1);
    }
    unsigned int days1= d1.totalNumOfDays(), days2 = d2.totalNumOfDays(), res = days1-days2;
    return daysToDate(res);
}
