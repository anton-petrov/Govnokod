//
// Created by Anton Petrov on 04.06.2022.
//

#include "User.h"

User::User(const std::string &name) : name(name) {}

std::string User::getName() {
    return this->name;
}