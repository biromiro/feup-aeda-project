//
// Created by Danny on 17/11/2020.
//

#include "nicknameNotFound.h"

#include <utility>

NicknameNotFound::NicknameNotFound(std::string nickname, const std::string &message): nickname(std::move(std::move(nickname))), message(message), std::invalid_argument(message) {}

const std::string & NicknameNotFound::getMessage() { return message; }