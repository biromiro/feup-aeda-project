//
// Created by emanu on 19-Nov-20.
//

#include "adminAlreadySet.h"

AdminAlreadySet::AdminAlreadySet(std::shared_ptr<Admin> admin, const std::string &message) :admin(std::move(std::move(admin))),message(message),std::invalid_argument(message){}

const std::string & AdminAlreadySet::getMessage() {return message;}
