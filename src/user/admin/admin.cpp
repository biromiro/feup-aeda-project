//
// Created by biromiro on 18/10/20.
//

#include "admin.h"

Admin::Admin() : User(ADMIN){}

Admin::Admin(Date birthDate, std::string name, std::string nickname): User(birthDate,std::move(name),std::move(nickname), ADMIN) {}

void Admin::readData(std::ifstream &ifs) {
    User::readData(ifs);
}

void Admin::writeData(std::ofstream &ofs) {
    User::writeData(ofs);
}
