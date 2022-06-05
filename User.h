//
// Created by Anton Petrov on 04.06.2022.
//

#ifndef CPP23_USER_H
#define CPP23_USER_H

#include <string>

class User {
public:
    std::string name;

    explicit User(std::string name);
    [[nodiscard]] std::string getName() const;
};


#endif //CPP23_USER_H
