//
// Created by Danny on 17/11/2020.
//

#ifndef PROJECT_NICKNAMENOTFOUND_H
#define PROJECT_NICKNAMENOTFOUND_H

#include <iostream>
#include <exception>

class NicknameNotFound : std::invalid_argument {
public:
    NicknameNotFound(std::string nickname, const std::string & message);
    const std::string & getMessage();
private:
    std::string nickname;
    std::string message;
};

#endif //PROJECT_NICKNAMENOTFOUND_H
