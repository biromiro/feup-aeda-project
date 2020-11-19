//
// Created by Danny on 18/11/2020.
//

#ifndef PROJECT_NICKNAMEALREADYADDED_H
#define PROJECT_NICKNAMEALREADYADDED_H

#include <iostream>
#include <exception>

class NicknameAlreadyAdded : public std::invalid_argument {
public:
    NicknameAlreadyAdded(std::string nickname, const std::string & message);

    const std::string &getNickname() const;

private:
    std::string nickname;
};

#endif //PROJECT_NICKNAMEALREADYADDED_H
