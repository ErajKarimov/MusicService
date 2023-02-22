// Copyright 2023  Eraj eradzh@2017@mail.ru

#ifndef INCLUDE_SONG_HPP
#define INCLUDE_SONG_HPP
#include <string>

class Song {
public:
    std::string name;
    int duration;
    Song(const std::string name, int duration);
};

#endif //INCLUDE_SONG_HPP
