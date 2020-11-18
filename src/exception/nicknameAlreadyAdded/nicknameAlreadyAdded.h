//
// Created by Danny on 18/11/2020.
//

#ifndef PROJECT_NICKNAMEALREADYADDED_H
#define PROJECT_NICKNAMEALREADYADDED_H

#include <iostream>
#include <exception>

class NicknameAlreadyAdded : std::invalid_argument {
public:
    NicknameAlreadyAdded(std::string nickname, const std::string & message);
    const std::string & getMessage();
private:
    std::string nickname;
    std::string message;
};

#endif //PROJECT_NICKNAMEALREADYADDED_H
