#include <Server.hpp>

Playlist *checkClient(grpc::ServerContext *context, std::map<std::string, std::unique_ptr<Playlist>> &playlists) {
    auto client_id = context->peer();
    auto end = std::remove_if(client_id.begin(), client_id.end(),
                              [](char c) { return !std::isalnum(c); });
    client_id.erase(end, client_id.end());
    if (playlists.count(client_id) == 0) {
        std::cout << "Creating new playlist for client " << client_id << std::endl;
        playlists[client_id] = std::make_unique<Playlist>(client_id);
    }
    return playlists[client_id].get();
}

grpc::Status PlaylistServiceImpl::Play(grpc::ServerContext *context, const playlist::Empty *request,
                                       playlist::Empty *response) {
    auto playlist = checkClient(context, playlists);
    playlist->Play();
    return grpc::Status::OK;
}

grpc::Status PlaylistServiceImpl::Pause(grpc::ServerContext *context, const playlist::Empty *request,
                                        playlist::Empty *response) {
    auto playlist = checkClient(context, playlists);
    playlist->Pause();
    return grpc::Status::OK;
}

grpc::Status PlaylistServiceImpl::AddSong(grpc::ServerContext *context, const playlist::Song *request,
                                          playlist::Empty *response) {
    Song song(request->name(), request->duration());
    auto playlist = checkClient(context, playlists);
    playlist->AddSong(song);
    return grpc::Status::OK;
}

grpc::Status PlaylistServiceImpl::NextPrev(grpc::ServerContext *context, const playlist::NextPrevRequest *request,
                                           playlist::Empty *response) {
    auto playlist = checkClient(context, playlists);
    if (request->direction() == playlist::NextPrevRequest::NEXT) {
        playlist->Next();
    } else {
        playlist->Prev();
    }
    return grpc::Status::OK;
}

grpc::Status PlaylistServiceImpl::GetAllSongs(grpc::ServerContext *context, const playlist::Empty *request,
                                              playlist::SongList *response) {
    auto playlist = checkClient(context, playlists);
    for (const auto &song: playlist->GetSongs()) {
        auto song_proto = response->add_songs();
        song_proto->set_name(song.GetName());
        song_proto->set_duration(song.GetDuration());
    }
    return grpc::Status::OK;
}

grpc::Status PlaylistServiceImpl::UpdateSong(grpc::ServerContext *context, const playlist::Song *request,
                                             playlist::Empty *response) {
    Song song(request->name(), request->duration());
    auto playlist = checkClient(context, playlists);
    playlist->UpdateSong(song.GetName(), song.GetDuration());
    return grpc::Status::OK;
}

grpc::Status PlaylistServiceImpl::DeleteSong(grpc::ServerContext *context, const playlist::Song *request,
                                             playlist::Empty *response) {
    Song song(request->name(), request->duration());
    auto playlist = checkClient(context, playlists);
    playlist->DeleteSong(song.GetName(), song.GetDuration());
    return grpc::Status::OK;
}

grpc::Status PlaylistServiceImpl::UpdateConfig(grpc::ServerContext *context, const playlist::Empty *request,
                                               playlist::Empty *response) {
    auto playlist = checkClient(context, playlists);
    playlist->UpdateConfig();
    return grpc::Status::OK;
}
