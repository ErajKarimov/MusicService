// Copyright 2023  Eraj eradzh@2017@mail.ru

#include <Song.hpp>
#include <stdexcept>

Song::Song(const std::string name, int duration) : name(name) {
    if (duration < 0) {
        throw std::invalid_argument("Duration cannot be negative");
    }
    this->duration = duration;
}



