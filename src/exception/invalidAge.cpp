//
// Created by nrtc on 14/11/2020.
//

#include "invalidAge.h"


InvalidAge::InvalidAge(unsigned int age, const std::string &arg) : invalid_argument(arg), age(age), message(arg) {}

const std::string &InvalidAge::getMessage() {
    return message;
}
