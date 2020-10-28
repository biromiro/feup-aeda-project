//
// Created by biromiro on 27/10/20.
//

#ifndef PROJECT_ADMIN_MANAGER_H
#define PROJECT_ADMIN_MANAGER_H

#include "admin.h"
#include "../user_manager.h"


class AdminManager{
public:
    AdminManager(UserManager* userManager);
    bool add(Admin* admin);
    bool remove(Admin* admin);
    bool has(Admin* admin) const;
    bool has(std::string nickname) const;
    Admin* get(std::string nickname) const;
    void write(std::ostream os) const;
    void read(std::ostream os);

private:
    std::vector<Admin*> admin;
    UserManager* userManager;
};

#endif //PROJECT_ADMIN_MANAGER_H
