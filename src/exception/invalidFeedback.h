//
// Created by Danny on 17/11/2020.
//

#ifndef PROJECT_INVALIDFEEDBACK_H
#define PROJECT_INVALIDFEEDBACK_H

#include <iostream>
#include <exception>

enum class FeedbackLikeSystem;

class InvalidFeedback : std::invalid_argument {
public:
    InvalidFeedback(enum FeedbackLikeSystem fb, const std::string & message);
    const std::string & getMessage();
private:
    enum FeedbackLikeSystem fb;
    std::string message;
};

#endif //PROJECT_INVALIDFEEDBACK_H
