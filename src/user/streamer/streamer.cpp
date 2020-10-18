//
// Created by biromiro on 18/10/20.
//

#include "streamer.h"

Streamer::Streamer(unsigned int age, std::string name, std::string nickname): User(age,name,nickname) {
    if(age < 15){
        throw std::invalid_argument("Minimum Age Not Met");
    }
}

enum UserTypes Streamer::getUserType() const{
    return STREAMER;
}