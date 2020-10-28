//
// Created by biromiro on 27/10/20.
//

#ifndef PROJECT_USER_MANAGER_H
#include <ostream>
#include "user.h"

class UserManager{
public:
    UserManager();
    bool add(User* user);
    bool remove(User* user);
    bool has(User* user) const;
    bool has(std::string nickname) const;
    User* get(std::string nickname) const;
    void write(std::ostream os) const;
    void read(std::ostream os);

private:
    std::vector<User*> user;
};
#define PROJECT_USER_MANAGER_H

#endif //PROJECT_USER_MANAGER_H
