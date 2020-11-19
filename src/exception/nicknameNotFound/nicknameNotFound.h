//
// Created by Danny on 17/11/2020.
//

#ifndef PROJECT_NICKNAMENOTFOUND_H
#define PROJECT_NICKNAMENOTFOUND_H

#include <iostream>
#include <exception>

class NicknameNotFound : public std::invalid_argument {
public:
    NicknameNotFound(std::string nickname, const std::string & message);

    const std::string &getNickname() const;

private:
    std::string nickname;
};

#endif //PROJECT_NICKNAMENOTFOUND_H
