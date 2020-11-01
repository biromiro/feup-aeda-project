//
// Created by biromiro on 16/10/20.
//

#include "user.h"

#include <utility>

User::User(Date birthDate, std::string name, std::string nickname, enum UserTypes type) :
        birthDate(birthDate), joinDate(Date()), name(std::move(name)), nickname(std::move(nickname)), type(type){}

unsigned int User::getAge() const{
    unsigned int age = timeElapsed(birthDate,Date()).getYear();
    return age;
}

const std::string &User::getName() const {
    return name;
}

const std::string &User::getNickname() const{
    return nickname;
}

const Date& User::getBirthDate() const {
    return birthDate;
}

const Date& User::getJoinDate() const {
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

enum UserTypes User::getUserType() const{
    return type;
}

