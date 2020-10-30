//
// Created by biromiro on 16/10/20.
//

#include "user.h"

User::User(Date birthDate, std::string name, std::string nickname, enum UserTypes type) :
        birthDate(birthDate), joinDate(Date()), name(name), nickname(nickname), type(type){}

unsigned int User::getAge() const{
    return timeElapsed(birthDate,Date()).getYear();
}

const std::string &User::getName() const {
    return name;
}

const std::string &User::getNickname() const{
    return nickname;
}

Date User::getBirthDate() const {
    return birthDate;
}

Date User::getJoinDate() const {
    return joinDate;
}

void User::updateBirthDate(const Date &d1) {
    birthDate = d1;
}

void User::updateName(const std::string& newName) {
    name = newName;
}

void User::updateNickname(const std::string& newNickname) {
    nickname = newNickname;
}
