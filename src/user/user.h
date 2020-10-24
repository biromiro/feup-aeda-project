//
// Created by biromiro on 13/10/20.
//

#include <iostream>
#include <string>

#ifndef PROJECT_USER_H
#define PROJECT_USER_H

enum UserTypes{
    STREAMER,
    VIEWER,
    ADMIN
};

class User{
public:
    User(unsigned int age, std::string name, std::string nickname, enum UserTypes type);
    unsigned int getAge() const;
    const std::string &getName() const;
    const std::string &getNickname() const;
    virtual enum UserTypes getUserType() const = 0;

protected:
    unsigned int age;
    std::string name;
    std::string nickname;
    enum UserTypes type;
};

#endif //PROJECT_USER_H
