cmake_minimum_required(VERSION 3.23)
project(check)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(Include protos)

file(GLOB SERVER
        Include/Playlist.hpp Include/Song.hpp Include/Server.hpp Include/json.hpp
        Source/Server/Playlist.cpp Source/Server/server.cpp Source/Server/main_server.cpp
        protos/playlist.pb.cc protos/playlist.grpc.pb.cc
        )
file(GLOB CLIENT
        Include/Client.hpp
        Source/Client/main_client.cpp  Source/Client/client.cpp
        protos/playlist.pb.cc protos/playlist.grpc.pb.cc
        )
add_executable(${PROJECT_NAME}
    Source/test.cpp Include/Playlist.hpp Source/Server/Playlist.cpp Include/Song.hpp)
add_executable(grpc-client ${CLIENT} )
add_executable(grpc-server ${SERVER} )
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} pthread)
target_include_directories(grpc-client PRIVATE ${PROTOBUF_INCLUDE_DIRS})
target_include_directories(grpc-server PRIVATE ${PROTOBUF_INCLUDE_DIRS})
target_link_libraries(grpc-client PRIVATE gRPC::grpc++_unsecure ${PROTOBUF_LIBRARIES})
target_link_libraries(grpc-server PRIVATE gRPC::grpc++_unsecure ${PROTOBUF_LIBRARIES})
