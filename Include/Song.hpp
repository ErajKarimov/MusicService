// Copyright 2023  Eraj eradzh@2017@mail.ru

#ifndef INCLUDE_SONG_HPP
#define INCLUDE_SONG_HPP

#include <stdexcept>
#include <string>

class Song {
private:
    std::string name;
    int duration;
public:
    Song(std::string name, int duration) : name(name) {
        if (duration < 0) {
            throw std::invalid_argument("Duration cannot be negative");
        }
        this->duration = duration;
    }

    std::string GetName() const {
        return this->name;
    }

    int GetDuration() const {
        return this->duration;
    }
    void SetDuration(const int new_duration) {
        duration = new_duration;
    }
};

#endif //INCLUDE_SONG_HPP
