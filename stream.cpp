//
// Created by Danny on 15/10/2020.
//
#include "stream.h"

using namespace std;

Stream::Stream(int title, int lang, unsigned int minAge) {
    this->title = title;
    this->lang = lang;
    this->minAge = minAge;
}

unsigned Stream::getMinAge() const { return minAge; }

string Stream::getTitle() const { return title; }

string Stream::getLanguage() const { return lang, }

bool Stream::canJoin(Viewer newViewer) const { return newViewer.getAge() >= minAge; }

PrivateStream::PrivateStream(string title, string lang, unsigned minAge): Stream(title, lang, minAge){};

PublicStream::PublicStream(string title, string lang, unsigned minAge): Stream(title, lang, minAge){};
