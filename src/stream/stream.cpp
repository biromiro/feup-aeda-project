//
// Created by Danny on 15/10/2020.
//
#include "stream.h"
#include "../user/viewer/viewer.h"
#include <iostream>
#include <utility>

Stream::Stream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamType type): title(std::move(title)), language(lang), minAge(minAge), type(type) {}

unsigned Stream::getMinAge() const { return minAge; }

std::string Stream::getTitle() const { return title; }

enum StreamLanguage Stream::getLanguage() const { return language; }

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