// Copyright 2023  Eraj eradzh@2017@mail.ru

#ifndef INCLUDE_SERVER_HPP
#define INCLUDE_SERVER_HPP

#include <grpcpp/grpcpp.h>
#include <grpcpp/server_context.h>
#include <playlist.grpc.pb.h>
#include <Playlist.hpp>

class PlaylistServiceImpl final : public playlist::Playlist::Service {
public:

    grpc::Status AddSong(grpc::ServerContext *context, const playlist::Song *request,
                              playlist::Empty *response)  override;

    grpc::Status DeleteSong(grpc::ServerContext *context, const playlist::Song *request,
                              playlist::Empty *response)  override;

    grpc::Status GetAllSongs(grpc::ServerContext *context, const playlist::Empty *request,
                              playlist::SongList *response) override;

    grpc::Status NextPrev(grpc::ServerContext *context, const playlist::NextPrevRequest *request,
                              playlist::Empty *response) override;

    grpc::Status Pause(grpc::ServerContext *context, const playlist::Empty *request,
                              playlist::Empty *response) override;

    grpc::Status Play(grpc::ServerContext *context, const playlist::Empty *request,
                              playlist::Empty *response) override;

    grpc::Status UpdateConfig(grpc::ServerContext *context, const playlist::Empty *request,
                              playlist::Empty *response) override;

    grpc::Status UpdateSong(grpc::ServerContext *context, const playlist::Song *request,
                              playlist::Empty *response) override;

private:
    std::map<std::string, std::unique_ptr<Playlist>> playlists;
};

#endif //INCLUDE_SERVER_HPP
