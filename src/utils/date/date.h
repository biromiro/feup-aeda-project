//
// Created by biromiro on 18/10/20.
//

#ifndef PROJECT_DATE_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

/**
 * @file date.cpp
 *
 * @brief Date class for the project
 *
 * @ingroup utils
 */

/**
 * Implementation of a Date Class
 *
 * Wraps information into a date format
 */
class Date{
public:

    /**
     * Date default constructor
     */
    Date();

    /**
     * Date parameter constructor
     *
     * @param y the year
     * @param m the month
     * @param d the day
     */
    Date(unsigned int y, unsigned int m, unsigned int d);

    /**
     * Date parameter constructor with hours
     *
     * @param y the year
     * @param m the month
     * @param d the day
     * @param h the hour
     * @param min the minute
     * @param sec the second
     */
    Date(unsigned int y, unsigned int m, unsigned int d, unsigned int h, unsigned int min, unsigned int sec);

    /**
     * Date constructor by string
     *
     * @param yearMonthDay the string representing the date, must be in format yyyy/MM/dd
     */
    explicit Date(const std::string& yearMonthDay);

    /**
     * Sets the current year
     *
     * @param y the year to set
     */
    void setYear(unsigned int y);

    /**
     * Set the current month
     *
     * @param m the month to set
     */
    void setMonth(unsigned int m);

    /**
     * Set the current day
     *
     * @param d the day to set
     */
    void setDay(unsigned int d);

    /**
     * Set the current hour
     *
     * @param hours the hour to set
     */
    void setHours(unsigned int hours);

    /**
     * Set the current minute
     *
     * @param minutes the minute to set
     */
    void setMinutes(unsigned int minutes);

    /**
     * Set the current second
     *
     * @param seconds the second to set
     */
    void setSeconds(unsigned int seconds);

    /**
     * Set the current date
     *
     * @param y the year
     * @param m the month
     * @param d the day
     */
    void setDate(unsigned int y, unsigned int m, unsigned int d);

    /**
     * Get the current year
     *
     * @return the year
     */
    [[nodiscard]] unsigned int getYear() const;

    /**
     * Get the current month
     *
     * @return the month
     */
    [[nodiscard]] unsigned int getMonth() const;

    /**
     * Get the current day
     *
     * @return the day
     */
    [[nodiscard]] unsigned int getDay() const;

    /**
     * Get the current hour
     *
     * @return the hour
     */
    [[nodiscard]] unsigned int getHours() const;

    /**
     * Get the current minute
     *
     * @return the minute
     */
    [[nodiscard]] unsigned int getMinutes() const;

    /**
     * Get the current second
     *
     * @return the second
     */
    [[nodiscard]] unsigned int getSeconds() const;

    /**
     * Get the current date via string
     *
     * @return the date
     */
    [[nodiscard]] std::string getDate() const;

    /**
     * Outputs the date
     */
    void show() const;

    /**
     * Get the total number of days of a given
     *
     * @return
     */
    [[nodiscard]] unsigned int totalNumOfDays() const;

    /**
     * Checks if the current date is valid
     *
     * @return the validity of the date
     */
    [[nodiscard]] bool isValid() const;

    /**
     * Compares the date to another to see if they're the same
     *
     * @param date the date to compare
     * @return true if they're the same, false otherwise
     */
    [[nodiscard]] bool isEqualTo(const Date &date) const;

    /**
     * Checks if the current date is after the one given by parameter
     *
     * @param date the date to compare
     * @return true if it is, false otherwise
     */
    [[nodiscard]] bool isAfter(const Date &date) const;

    /**
     * Checks if the current date is after the one given by parameter
     *
     * @param date the date to compare
     * @return true if it is, false otherwise
     */
    [[nodiscard]] bool isBefore(const Date &date) const;

    /**
     * Output operator overload
     *
     * @param os the output stream
     * @param date the date to output
     * @return the stream given as parameter
     */
    friend std::ostream &operator<<(std::ostream &os, const Date &date);

    /**
    * Input operator overload
    *
    * @param is the input stream
    * @param date the date to output
    * @return the stream given as parameter
    */
    friend std::istream &operator>>(std::istream &is, Date &date);

    /**
     * Operator of equality overload
     *
     * @param rhs the date to compare
     * @return true if it is, false otherwise
     */
    bool operator==(const Date &rhs) const;

    /**
     * Operator of inequality overload
     *
      @param rhs the date to compare
     * @return true if it is, false otherwise
     */
    bool operator!=(const Date &rhs) const;

    /**
    * 'Smaller' Operator overload
    *
     @param rhs the date to compare
    * @return true if it is, false otherwise
    */
    bool operator<(const Date &rhs) const;

    /**
    * 'Greater' Operator overload
    *
     @param rhs the date to compare
    * @return true if it is, false otherwise
    */
    bool operator>(const Date &rhs) const;

    /**
    * 'Smaller or Equal' Operator overload
    *
     @param rhs the date to compare
    * @return true if it is, false otherwise
    */
    bool operator<=(const Date &rhs) const;

    /**
    * 'Greater or Equal' Operator overload
    *
     @param rhs the date to compare
    * @return true if it is, false otherwise
    */
    bool operator>=(const Date &rhs) const;
private:
    unsigned int year{};
    unsigned int month{};
    unsigned int day{};
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;
};
/**
 * Converts a raw number of days into a Date
 *
 * @param days the total number of days
 * @return the date which has that number of days (counting from 1/1/1)
 */
Date daysToDate(unsigned int days);

/**
 * Calculates the time elapsed between two dates
 *
 * @param d1 the first date
 * @param d2 the second date
 * @return the date corresponding to the time elapsed between the two dates
 */
Date timeElapsed(const Date& d1, const Date& d2);

/**
 * Gets the number of days in a given month of a given year
 *
 * @param year the year
 * @param month the month
 * @return The number of days of that month
 */
unsigned int numberOfDays(unsigned int year, unsigned int month);

/**
 * Checks if a given year is a leap year
 *
 * @param y the year
 * @return true if it is, false otherwise
 */
bool isLeap(unsigned int y);

#define PROJECT_DATE_H

#endif //PROJECT_DATE_H
