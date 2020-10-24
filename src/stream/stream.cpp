//
// Created by Danny on 15/10/2020.
//
#include "stream.h"
#include "../user/viewer/viewer.h"
#include <iostream>

Stream::Stream(std::string title, std::string lang, unsigned int minAge, enum StreamType type): title(title), lang(lang), minAge(minAge), type(type) {}

unsigned Stream::getMinAge() const { return minAge; }

std::string Stream::getTitle() const { return title; }

std::string Stream::getLanguage() const { return lang; }

bool Stream::canJoin(Viewer* newViewer) const { return newViewer->getAge() >= minAge; }

bool Stream::getFeedback(enum FeedbackLikeSystem feedback) {
    if(feedback == LIKE)
        votingSystem.first++;
    else if(feedback == DISLIKE)
        votingSystem.second++;
    else
        return false;
    return true;
}