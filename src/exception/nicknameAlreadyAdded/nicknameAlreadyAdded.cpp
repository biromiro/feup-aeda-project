//
// Created by Danny on 18/11/2020.
//

#include "nicknameAlreadyAdded.h"

#include <utility>

NicknameAlreadyAdded::NicknameAlreadyAdded(std::string nickname, const std::string & message): nickname(std::move(std::move(nickname))), message(message), std::invalid_argument(message) {}

const std::string & NicknameAlreadyAdded::getMessage() { return message; }
