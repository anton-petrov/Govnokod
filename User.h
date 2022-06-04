//
// Created by Anton Petrov on 04.06.2022.
//

#ifndef CPP23_USER_H
#define CPP23_USER_H

#include <string>

class User {
public:
    std::string name;

    User(const std::string &name);
    std::string getName();
};


#endif //CPP23_USER_H
