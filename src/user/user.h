//
// Created by biromiro on 13/10/20.
//

#include <iostream>
#include <string>
#include <vector>
#include "../utils/date/date.h"

#ifndef PROJECT_USER_H
#define PROJECT_USER_H

/**
 * Defines what type of user an instanciation of the User Class is
 */
enum UserTypes{
    STREAMER,
    VIEWER,
    ADMIN
};

class User{
public:
    /**
     * Constructor of the User class
     *
     * @param birthDate the date of birth of the user
     * @param name the name of the user
     * @param nickname the nickname of the user
     * @param type the type of user
     */
    User(Date birthDate, std::string name, std::string nickname, enum UserTypes type);

    /**
     * Getter of the birth date of the User
     *
     * @return user's birth date
     */
    Date getBirthDate() const;

    /**
     * Gets the age of the user in years
     *
     * @return user's age
     */
    unsigned int getAge() const;

    /**
     * Getter of the join date of the User on the platform
     *
     * @return user's join date
     */
    Date getJoinDate() const;

    /**
     * Getter of the name of the user
     *
     * @return user's name
     */
    const std::string &getName() const;

    /**
     * Getter of the nickname of the user
     *
     * @return user's nickname
     */
    const std::string &getNickname() const;

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
     * Getter of the type of User
     *
     * @return the user's type
     */
    virtual enum UserTypes getUserType() const = 0;

protected:
    Date birthDate;
    Date joinDate;
    std::string name;
    std::string nickname;
    enum UserTypes type;
};

#endif //PROJECT_USER_H
