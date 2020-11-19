//
// Created by emanu on 19-Nov-20.
//

#ifndef PROJECT_ADMINNOTSET_H
#define PROJECT_ADMINNOTSET_H

#include <iostream>
#include <exception>
#include <memory>
#include "../../model/user/admin/admin.h"

class AdminNotSet : public std::runtime_error{
public:
    AdminNotSet(std::shared_ptr<Admin> admin,const std::string & message);

    const std::shared_ptr<Admin> &getAdmin() const;

private:
    std::shared_ptr<Admin> admin;
};


#endif //PROJECT_ADMINNOTSET_H
