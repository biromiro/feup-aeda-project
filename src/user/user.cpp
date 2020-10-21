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
User::User(size_t age, std::string name, std::string nickname, enum UserTypes type) : age(age), name(name), nickname(nickname), type(type){}

size_t User::getAge() const{
    return age;
}

const std::string &User::getName() const {
    return name;
}

const std::string &User::getNickname() const{
    return nickname;
}
