// Copyright 2023  Eraj eradzh@2017@mail.ru

#include <Client.hpp>

void PlaylistClient::Play() {
    Empty request;
    Empty response;
    ClientContext context;
    Status status = stub_->Play(&context, request, &response);
    if (status.ok()) {
        std::cout << "Playback started" << std::endl;
    } else {
        std::cout << "RPC failed: " << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void PlaylistClient::Pause() {
    Empty request;
    Empty response;
    ClientContext context;
    Status status = stub_->Pause(&context, request, &response);
    if (status.ok()) {
        std::cout << "Playback paused" << std::endl;
    } else {
        std::cout << "RPC failed: " << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void PlaylistClient::AddSong(std::string &name, int &duration) {
    Song request;
    request.set_name(name);
    request.set_duration(duration);
    Empty response;
    ClientContext context;
    Status status = stub_->AddSong(&context, request, &response);
    if (status.ok()) {
        std::cout << "Song added to playlist" << std::endl;
    } else {
        std::cout << "RPC failed: " << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void PlaylistClient::Next() {
    NextPrevRequest request;
    request.set_direction(NextPrevRequest::NEXT);
    Empty response;
    ClientContext context;
    Status status = stub_->NextPrev(&context, request, &response);
    if (status.ok()) {
        std::cout << "Next song playing" << std::endl;
    } else {
        std::cout << "RPC failed: " << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void PlaylistClient::Prev() {
    NextPrevRequest request;
    request.set_direction(NextPrevRequest::PREV);
    Empty response;
    ClientContext context;
    Status status = stub_->NextPrev(&context, request, &response);
    if (status.ok()) {
        std::cout << "Previous song playing" << std::endl;
    } else {
        std::cout << "RPC failed: " << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void PlaylistClient::UpdateSong(std::string &name, int &duration) {
    Song request;
    request.set_name(name);
    request.set_duration(duration);
    Empty response;
    ClientContext context;
    Status status = stub_->UpdateSong(&context, request, &response);
    if (status.ok()) {
        std::cout << "Song successfully edited" << std::endl;
    } else {
        std::cout << "RPC failed: " << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void PlaylistClient::DeleteSong(std::string &name) {
    int duration{};
    Song request;
    request.set_name(name);
    request.set_duration(duration);
    Empty response;
    ClientContext context;
    Status status = stub_->DeleteSong(&context, request, &response);
    if (status.ok()) {
        std::cout << "Song successfully deleted" << std::endl;
    } else {
        std::cout << "RPC failed: " << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void PlaylistClient::UpdateConfig() {
    Empty request;
    Empty response;
    ClientContext context;
    Status status = stub_->UpdateConfig(&context, request, &response);
    if (status.ok()) {
        std::cout << "Bye" << std::endl;
    } else {
        std::cout << "RPC failed: " << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void PlaylistClient::PrintAllSongs() {
    playlist::Empty request;
    playlist::SongList response;
    ClientContext context;

    Status status = stub_->GetAllSongs(&context, request, &response);
    if (status.ok()) {
        for (const auto &song: response.songs()) {
            std::cout << "Song: " << song.name() << " Duration: " << song.duration() << "s" << std::endl;
        }
    } else {
        std::cout << "Error: " << status.error_message() << std::endl;
    }
}


