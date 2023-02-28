// Copyright 2023  Eraj eradzh@2017@mail.ru

#ifndef INCLUDE_CLIENT_HPP
#define INCLUDE_CLIENT_HPP

#include <iostream>
#include <memory>
#include <thread>
#include <grpcpp/grpcpp.h>
#include "playlist.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using playlist::Empty;
using playlist::NextPrevRequest;
using playlist::Song;
using playlist::Playlist;

class PlaylistClient {
public:
    explicit PlaylistClient(const std::shared_ptr<Channel> &channel)
            : stub_(Playlist::NewStub(channel)) {}

    void Play();

    void Pause();

    void AddSong(std::string &name, int &duration);

    void Next();

    void Prev();

    void UpdateSong(std::string &name, int &duration);

    void DeleteSong(std::string &name);

    void UpdateConfig();

    void PrintAllSongs();

private:
    std::unique_ptr<Playlist::Stub> stub_;
};

#endif //INCLUDE_CLIENT_HPP
