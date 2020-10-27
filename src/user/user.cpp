//
// Created by biromiro on 16/10/20.
//

#include <iostream>
#include "user.h"

/**
 * Constructor
 * @param age
 * @param name
 * @param nickname
 * @param type
 */
User::User(Date birthDate, std::string name, std::string nickname, enum UserTypes type) : birthDate(birthDate), name(name), nickname(nickname), type(type){}

unsigned int User::getAge() const{
    return timeElapsed(birthDate,Date()).getYear();
}

const std::string &User::getName() const {
    return name;
}

const std::string &User::getNickname() const{
    return nickname;
}
