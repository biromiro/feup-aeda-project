//
// Created by biromiro on 13/10/20.
//

#ifndef PROJECT_USER_H
#define PROJECT_USER_H


class User{
public:
    User();
    unsigned int getAge();

private:
    unsigned int age;
};

class Viewer: public User{

};

#endif //PROJECT_USER_H
