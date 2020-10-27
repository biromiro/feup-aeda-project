//
// Created by biromiro on 18/10/20.
//

#include "streamer.h"

Streamer::Streamer(Date birthDate, std::string name, std::string nickname): User(birthDate,name,nickname, STREAMER) {
    if(getAge() < 15){
        throw std::invalid_argument("Minimum Age Not Met");
    }
}

enum UserTypes Streamer::getUserType() const{
    return type;
}