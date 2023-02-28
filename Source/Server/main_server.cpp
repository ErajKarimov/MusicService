// Copyright 2023  Eraj eradzh@2017@mail.ru

#include <grpcpp/grpcpp.h>
#include <playlist.grpc.pb.h>
#include <Playlist.hpp>
#include <Server.hpp>

int main(int argc, char **argv) {
    std::string server_address("0.0.0.0:50051");

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(new PlaylistServiceImpl());

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
    return 0;
}
