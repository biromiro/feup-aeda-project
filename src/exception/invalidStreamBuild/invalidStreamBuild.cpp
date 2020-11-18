//
// Created by Danny on 18/11/2020.
//

#include "invalidStreamBuild.h"

InvalidStreamBuild::InvalidStreamBuild(const std::string &message) : message(message), std::invalid_argument(message) {}

const std::string & InvalidStreamBuild::getMessage() { return message; }