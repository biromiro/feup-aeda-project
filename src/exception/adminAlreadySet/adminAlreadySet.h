//
// Created by emanu on 19-Nov-20.
//

#ifndef PROJECT_ADMINALREADYSET_H
#define PROJECT_ADMINALREADYSET_H


#include <iostream>
#include <exception>
#include <memory>
#include "../../model/user/admin/admin.h"

class AdminAlreadySet: std::invalid_argument{
public:
    AdminAlreadySet(std::shared_ptr<Admin> admin,const std::string & message);
    const std::string & getMessage();
private:
    std::shared_ptr<Admin> admin;
    std::string message;
};

#endif //PROJECT_ADMINALREADYSET_H
