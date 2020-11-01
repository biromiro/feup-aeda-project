//
// Created by biromiro on 18/10/20.
//

#include "admin.h"


Admin::Admin(Date birthDate, std::string name, std::string nickname): User(birthDate,std::move(name),std::move(nickname), ADMIN) {}