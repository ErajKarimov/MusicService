FROM kalilinux/kali-dev:amd64

RUN apt-get update && \
    apt-get install -y cmake build-essential autoconf libtool pkg-config libgflags-dev libgtest-dev clang libc++-dev protobuf-compiler libprotobuf-dev git && \ 
    git clone --recurse-submodules -b v1.52.0 https://github.com/grpc/grpc && \
    cd grpc && \	
    mkdir -p cmake/build && \
    cd cmake/build && \
    cmake ../.. && \
    make -j$(nproc) && \
    make install && \
    ldconfig


VOLUME /SberMusic/Database/

COPY . /SberMusic

EXPOSE 50051

WORKDIR /SberMusic

