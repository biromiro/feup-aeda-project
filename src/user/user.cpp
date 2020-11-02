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

bool User::operator<(const User &rhs) const {
    if (joinDate < rhs.joinDate)
        return true;
    if (rhs.joinDate < joinDate)
        return false;
    if (birthDate < rhs.birthDate)
        return true;
    if (rhs.birthDate < birthDate)
        return false;
    if (nickname < rhs.nickname)
        return true;
    if (rhs.nickname < nickname)
        return false;
    if (name < rhs.name)
        return true;
    if (rhs.name < name)
        return false;
    return type < rhs.type;
}

bool User::operator>(const User &rhs) const {
    return rhs < *this;
}

bool User::operator<=(const User &rhs) const {
    return !(rhs < *this);
}

bool User::operator>=(const User &rhs) const {
    return !(*this < rhs);
}

bool User::operator==(const User &rhs) const {
    return nickname == rhs.nickname;
}

bool User::operator!=(const User &rhs) const {
    return !(rhs == *this);
}

bool charCmpEq(char a, char b) {
    return(toupper(a) == toupper(b));
}

bool charCmpSmaller(char a, char b) {
    return(toupper(a) < toupper(b));
}

bool operator<(std::string s1, std::string s2){
    if(s1.size()>s2.size())
        return !(s2<s1 || s2==s1);
    for(size_t index = 0; index<s1.size(); ++index){
        if(charCmpEq(s1[index],s2[index]))
            continue;
        if(charCmpSmaller(s1[index],s2[index])){
            return true;
        }
    }
    return true;
}

bool operator>(std::string s1, std::string s2){
    return !(s1<s2 || s1==s2);
}
bool operator<=(std::string s1, std::string s2){
    return s1<s2 || s1==s2;
}
bool operator>=(std::string s1, std::string s2){
    return s1>s2 || s1==s2;
}
bool operator==(std::string s1, std::string s2){
    return((s1.size() == s2.size()) && std::equal(s1.begin(), s1.end(), s2.begin(), charCmpEq));
}
bool operator!=(std::string s1, std::string s2){
    return !(s1 == s2);
}

std::ostream& operator<<(std::ostream& out, UserTypes f) {
    switch (f) {
        case VIEWER: out << "Viewer"; break;
        case STREAMER: out << "Streamer"; break;
        case ADMIN: out << "Admin"; break;
        default: out << int(f); break;
    }
    return out;
}


