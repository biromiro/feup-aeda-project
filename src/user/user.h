//
// Created by biromiro on 13/10/20.
//

#include <iostream>
#include <string>

#ifndef PROJECT_USER_H
#define PROJECT_USER_H

enum UserTypes{
    streamer,
    viewer,
    admin
};

class User{
public:
    User(unsigned int age, std::string name, std::string nickname);
    unsigned int getAge() const;
    const std::string &getName() const;
    const std::string &getNickname() const;
    virtual enum UserTypes getUserType() = 0;

protected:
    unsigned int age;
    std::string name;
    std::string nickname;
};

#endif //PROJECT_USER_H
