//
// Created by Danny on 17/11/2020.
//

#ifndef PROJECT_INVALIDFEEDBACK_H
#define PROJECT_INVALIDFEEDBACK_H

#include <iostream>
#include <exception>

enum class FeedbackLikeSystem;

class InvalidFeedback : public std::invalid_argument {
public:
    InvalidFeedback(FeedbackLikeSystem fb, const std::string & message);

    FeedbackLikeSystem getFb() const;

private:
    enum FeedbackLikeSystem fb;
};

#endif //PROJECT_INVALIDFEEDBACK_H
