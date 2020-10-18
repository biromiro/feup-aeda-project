//
// Created by Danny on 15/10/2020.
//
#include "stream.h"
#include "../user/viewer/viewer.h"
#include <iostream>

Stream::Stream(std::string title, std::string lang, unsigned int minAge) {
    this->title = title;
    this->lang = lang;
    this->minAge = minAge;
}

unsigned Stream::getMinAge() const { return minAge; }

std::string Stream::getTitle() const { return title; }

std::string Stream::getLanguage() const { return lang; }

bool Stream::canJoin(Viewer* newViewer) const { return newViewer->getAge() >= minAge; }