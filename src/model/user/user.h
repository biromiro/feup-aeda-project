//
// Created by biromiro on 13/10/20.
//

#include <iostream>
#include <string>
#include <vector>
#include "../../utils/date/date.h"

#ifndef PROJECT_USER_H
#define PROJECT_USER_H

/**
 * Defines what type of user an instantiation of the User Class is
 */
enum class UserTypes{
    STREAMER,
    VIEWER,
    ADMIN
};

class User{
public:

    /**
     * Getter of the birth date of the User
     *
     * @return user's birth date
     */
    [[nodiscard]] const Date& getBirthDate() const;

    /**
     * Gets the age of the user in years
     *
     * @return user's age
     */
    [[nodiscard]] unsigned int getAge() const;

    /**
     * Getter of the join date of the User on the platform
     *
     * @return user's join date
     */
    [[nodiscard]] const Date& getJoinDate() const;

    /**
     * Getter of the name of the user
     *
     * @return user's name
     */
    [[nodiscard]] const std::string &getName() const;

    /**
     * Getter of the nickname of the user
     *
     * @return user's nickname
     */
    [[nodiscard]] const std::string &getNickname() const;

    /**
     * Getter of user's password
     *
     * @return user's password
     * */
    [[nodiscard]] const std::string &getPassword() const;

    /**
     * Sets/Updates the user's birthdate
     *
     * @param d1 new birthDate
     */
    void updateBirthDate(const Date& d1);

    /**
     * Sets/Updates the user's name
     *
     * @param newName new name
     */
    void updateName(const std::string& newName);

    /**
     * Sets/Updates the user's nickname
     *
     * @param newNickname new nickname
     */
    void updateNickname(const std::string& newNickname);

    /**
     * Update user's password
     *
     * @param password password to replace the current one
     * */
    void updatePassword(const std::string &password);

    /**
     * Getter of the type of User
     *
     * @return the user's type
     */
    [[nodiscard]] enum UserTypes getUserType() const;

    /**
    * Reads user data from file
    *
    * @param ifs File to read users from
    * */
    virtual void readData(std::ifstream& ifs);

    /**
     * Writes and updates viewer data to file
    *
    * @param ofs File to write viewers to
    * */
    virtual void writeData(std::ofstream& ofs);

    /**
     * Overloard of operator < to users
     *
     * @param rhs given user to compare
     * @return self < given user
     * */
    bool operator<(const User &rhs) const;

    /**
    * Overloard of operator > to viewers
     *
    * @param rhs given user to compare
    * @return self > given
    * */
    bool operator>(const User &rhs) const;

    /**
    * Overloard of operator <= to viewers
    *
    * @param rhs given user to compare
    * @return self <= given
    * */
    bool operator<=(const User &rhs) const;

    /**
    * Overloard of operator == to viewers
    *
    * @param rhs given user to compare
    * @return self == given
    * */
    bool operator==(const User &rhs) const;

    /**
    * Overloard of operator != to viewers
    *
    * @param rhs given user to compare
    * @return self != given
    * */
    bool operator!=(const User &rhs) const;

    /**
    * Overloard of operator >= to viewers
    *
    * @param rhs given user to compare
    * @return self >= given
    * */
    bool operator>=(const User &rhs) const;
protected:
    explicit User(enum UserTypes type);

    /**
     * Constructor of the User class
     *
     * @param birthDate the date of birth of the user
     * @param name the name of the user
     * @param nickname the nickname of the user
     * @param type the type of user
     */
    User(Date birthDate, std::string name, std::string nickname, enum UserTypes type, std::string password);

    Date birthDate;
    Date joinDate;
    std::string name;
    std::string nickname;
    enum UserTypes type;
    std::string password;
};

bool operator<(std::string s1, std::string s2);
bool operator>(const std::string& s1, const std::string& s2);
bool operator<=(const std::string& s1, const std::string& s2);
bool operator>=(const std::string& s1, const std::string& s2);
bool operator==(const std::string& s1, const std::string& s2);
bool operator!=(const std::string& s1, const std::string& s2);
std::ostream& operator<<(std::ostream& out, UserTypes f);

#endif //PROJECT_USER_H
