//
// Created by emanu on 19-Nov-20.
//

#ifndef PROJECT_ADMINALREADYSET_H
#define PROJECT_ADMINALREADYSET_H


#include <iostream>
#include <exception>
#include <memory>
#include "../../model/user/admin/admin.h"

class AdminAlreadySet: public std::invalid_argument{
public:
    const std::shared_ptr<Admin> &getAdmin() const;

    AdminAlreadySet(std::shared_ptr<Admin> admin,const std::string & message);
private:
    std::shared_ptr<Admin> admin;
};

#endif //PROJECT_ADMINALREADYSET_H
