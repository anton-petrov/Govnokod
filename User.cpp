//
// Created by Anton Petrov on 04.06.2022.
//

#include "User.h"

#include <utility>

User::User(std::string name) : name(std::move(name)) {}

std::string User::getName() const {
    return this->name;
}