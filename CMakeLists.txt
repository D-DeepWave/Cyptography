cmake_minimum_required(VERSION 3.13)
project(Cyptography)

set(CMAKE_CXX_STANDARD 14)

add_executable(Cyptography main.cpp Header/AffineCipher.h Header/BASE.h
        Header/Big.h Header/MD5.h Realize/AffineCipher.cpp Realize/BASE.cpp
         Realize/Big.cpp Realize/MD5.cpp Realize/Elgamal.cpp Header/Elgamal.h)