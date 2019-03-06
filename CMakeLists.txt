cmake_minimum_required(VERSION 3.13)
project(Cyptography)

set(CMAKE_CXX_STANDARD 14)
include_directories(.)
include_directories(Header)

add_executable(Cyptography
        Header/AffineCipher.h
        Header/BASE.h
        Header/Big.h
        Header/Elgamal.h
        Header/MD5.h
        Realize/AffineCipher.cpp
        Realize/BASE.cpp
        Realize/Big.cpp
        Realize/Elgamal.cpp
        Realize/MD5.cpp
        main.cpp
        Realize/RSA.cpp
        Header/RSA.h)