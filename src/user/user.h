//
// Created by biromiro on 13/10/20.
//

#include <iostream>
#include <string>
#include <vector>
#include "../utils/date/date.h"

#ifndef PROJECT_USER_H
#define PROJECT_USER_H

enum UserTypes{
    STREAMER,
    VIEWER,
    ADMIN
};

class User{
public:
    User(Date birthDate, std::string name, std::string nickname, enum UserTypes type);
    Date getBirthDate() const;
    unsigned int getAge() const;
    Date getJoinDate() const;
    const std::string &getName() const;
    const std::string &getNickname() const;
    void updateBirthDate(const Date& d1);
    void updateName(const std::string& newName);
    void updateNickname(const std::string& newNickname);
    virtual enum UserTypes getUserType() const = 0;

protected:
    Date birthDate;
    Date joinDate;
    std::string name;
    std::string nickname;
    enum UserTypes type;
};

#endif //PROJECT_USER_H
