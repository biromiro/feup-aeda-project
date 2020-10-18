//
// Created by biromiro on 18/10/20.
//

#include "viewer.h"


Viewer::Viewer(unsigned int age, std::string name, std::string nickname): User(age,name,nickname){
    if(age < 12){
        throw std::invalid_argument("Minimum Age Not Met");
    }
}

enum UserTypes Viewer::getUserType() const{
    return viewer;
}