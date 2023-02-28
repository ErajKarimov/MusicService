// Copyright 2023  Eraj eradzh@2017@mail.ru

#include <Playlist.hpp>

Playlist::Playlist(std::string &client_ID) {
    client_id = client_ID;
    current_song = songs.begin();
    LoadConfig();
}

void Playlist::AddSong(const Song &song) {
    std::lock_guard<std::mutex> guard(playlist_mutex);
    songs.push_back(song);
    std::cout << "Added song " << song.GetName() << " to playlist." << std::endl;
}

void Playlist::DeleteSong(const std::string &name, const int &duration) {
    if (playing) {
        std::cout << "To delete song, first pause current song" << std::endl;
        return;
    }
    auto search = std::find_if(songs.begin(), songs.end(),
                               [&name](const Song &a) { return a.GetName() == name; });
    if (search != songs.end()) {
        songs.erase(search);
    } else {
        std::cout << "Song not found in the playlist" << std::endl;
    }
}

void Playlist::Next() {
    std::lock_guard<std::mutex> guard(playlist_mutex);
    if (current_song == songs.end()) {
        std::cout << "End of playlist!" << std::endl;
        playing = false;
        return;
    }
    std::cout << "Next song is: ";
    ++current_song;
    if (current_song == songs.end()) {
        std::cout << "End of playlist!" << std::endl;
        playing = false;
    } else {
        std::cout << current_song->GetName() << std::endl;
    }
}

void Playlist::LoadConfig() {
    std::ifstream config_file("../Database/" + client_id + ".json");
    if (config_file.good()) {
        config_file >> config_;
    } else {
        std::cout << "Can't find config file" << std::endl;
        return;
    }
    for (const auto &song: config_["songs"]) {
        songs.push_back({song["name"], song["duration"]});
    }
    current_song = songs.begin();
}

void Playlist::Pause() {
    std::lock_guard<std::mutex> guard(playlist_mutex);
    if (!playing) {
        std::cout << "Playlist is not currently playing!" << std::endl;
        return;
    }
    if (paused) {
        std::cout << "Playlist is already paused!" << std::endl;
        return;
    }
    paused = true;
    time_paused = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
    std::cout << "Paused playback of " << current_song->GetName() << std::endl;
}

void Playlist::Play() {
    std::unique_lock<std::mutex> lock(playlist_mutex);
    if (songs.empty()) {
        std::cout << "Playlist is empty!" << std::endl;
        return;
    }
    if (!playing) {
        std::cout << "Playing playlist..." << std::endl;
        playing = true;
        time_paused = std::chrono::milliseconds(0);
        std::thread playback_thread(&Playlist::Resume, this);
        playback_thread.detach();
    }
    if (paused) {
        paused = false;
        std::cout << "Resuming playback of " << current_song->GetName() << std::endl;
    } else {
        if (current_song == songs.end()) {
            current_song = songs.begin();
        }
        std::cout << "Now playing " << current_song->GetName() << std::endl;
    }
}

void Playlist::Prev() {
    std::lock_guard<std::mutex> guard(playlist_mutex);
    if (songs.empty()) {
        std::cout << "Playlist is empty!" << std::endl;
        return;
    }
    if (current_song == songs.begin()) {
        std::cout << "Beginning of playlist!" << std::endl;
        return;
    }
    --current_song;
    std::cout << "Previous song: " << current_song->GetName() << std::endl;
}

void Playlist::Resume() {
    while (playing && current_song != songs.end()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(current_song->GetDuration() - time_paused.count()));
        std::unique_lock<std::mutex> lock(playlist_mutex);
        if (paused) {
            continue;
        }
        lock.unlock();
        Next();
        time_paused = std::chrono::milliseconds(0);
        lock.lock();
    }
    if (current_song == songs.end()) {
        std::cout << "End of playlist!" << std::endl;
        playing = false;
    }
}

void Playlist::UpdateConfig() {
    config_["songs"] = nlohmann::json::array();
    for (const auto &song: songs) {
        config_["songs"].push_back({{"name",     song.GetName()},
                                    {"duration", song.GetDuration()}});
    }
    SaveConfig();
}

void Playlist::UpdateSong(const std::string &name, const int &duration) {
    for (auto &song: songs) {
        if (song.GetName() == name) {
            song.SetDuration(duration);
            return;
        }
    }
    std::cout << "Song not found: " << name << std::endl;
}

void Playlist::SaveConfig() {
    std::ofstream config_file("../Database/" + client_id + ".json");
    if (config_file.good()) {
        config_file << config_.dump(4) << std::endl;
    }
}
