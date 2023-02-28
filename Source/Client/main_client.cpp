// Copyright 2023  Eraj eradzh@2017@mail.ru

#include <Client.hpp>
#include <csignal>

bool stop = false;

void handler(int) {
    std::cout << "Press any key to exit";
    stop = true;
}

int main(int argc, char **argv) {
    auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    PlaylistClient client(channel);
    std::string name;
    int duration;
    signal(SIGINT, &handler);

    while (!stop) {
        std::cout << "Enter command (play, pause, add, next, prev, update, delete, print, exit): ";
        std::string command;
        std::getline(std::cin, command);
        if (command == "play") {
            client.Play();
        } else if (command == "pause") {
            client.Pause();
        } else if (command == "next") {
            client.Next();
        } else if (command == "prev") {
            client.Prev();
        } else if (command == "add") {
            std::cout << "Enter song name: ";
            std::getline(std::cin, name);
            std::cout << "Enter song duration: ";
            std::cin >> duration;
            std::cin.ignore();
            client.AddSong(name, duration);
        } else if (command == "update") {
            std::cout << "Enter song name: ";
            std::getline(std::cin, name);
            std::cout << "Enter new song duration: ";
            std::cin >> duration;
            std::cin.ignore();
            client.UpdateSong(name, duration);
        } else if (command == "delete") {
            std::cout << "Enter song name: ";
            std::getline(std::cin, name);
            client.DeleteSong(name);
        } else if (command == "print") {
            client.PrintAllSongs();
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Invalid command. Please try again." << std::endl;
        }
    }
    client.UpdateConfig();
    channel.reset();
    return 0;
}
