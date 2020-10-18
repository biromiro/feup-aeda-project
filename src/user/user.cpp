//
// Created by biromiro on 16/10/20.
//

#include <iostream>
#include "user.h"

User::User(unsigned int age, std::string name, std::string nickname) : age(age), name(name), nickname(nickname){}

unsigned int User::getAge() const{
    return age;
}

const std::string &User::getName() const {
    return name;
}

const std::string &User::getNickname() const{
    return nickname;
}
