//
// Created by emanu on 19-Nov-20.
//

#ifndef PROJECT_ADMINNOTSET_H
#define PROJECT_ADMINNOTSET_H

#include <iostream>
#include <exception>
#include <memory>
#include "../../model/user/admin/admin.h"

class AdminNotSet : std::invalid_argument{
public:
    AdminNotSet(std::shared_ptr<Admin> admin,const std::string & message);
    const std::string & getMessage();
private:
    std::shared_ptr<Admin> admin;
    std::string message;
};


#endif //PROJECT_ADMINNOTSET_H
