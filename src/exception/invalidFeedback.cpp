//
// Created by Danny on 17/11/2020.
//

#include "invalidFeedback.h"

InvalidFeedback::InvalidFeedback(enum FeedbackLikeSystem fb, const std::string &message): fb(fb), message(message), std::invalid_argument(message) {}

const std::string & InvalidFeedback::getMessage() { return message; }
