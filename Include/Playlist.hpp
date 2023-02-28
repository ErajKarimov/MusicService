// Copyright 2023  Eraj eradzh@2017@mail.ru

#ifndef INCLUDE_PLAYLIST_HPP
#define INCLUDE_PLAYLIST_HPP

#include <Song.hpp>

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <mutex>
#include <string>
#include <thread>

#include <json.hpp>

class Playlist {
public:
    Playlist(std::string& client_id);

    void AddSong(const Song &song);

    void DeleteSong(const std::string &name, const int &duration);

    const std::list<Song> &GetSongs() const {
        return songs;
    }

    void Next();

    void Pause();

    void Play();

    void Prev();

    void UpdateConfig();

    void UpdateSong(const std::string &name, const int &duration);

private:
    std::list<Song> songs;
    std::chrono::milliseconds time_paused;
    std::mutex playlist_mutex;
    nlohmann::json config_;
    std::string client_id;

    void LoadConfig();

    void Resume();

    void SaveConfig();
public:
    std::list<Song>::iterator current_song = songs.begin();
    bool paused = false;
    bool playing = false;
};

#endif //INCLUDE_PLAYLIST_HPP
