cmake_minimum_required(VERSION 3.13)
project(cyptography)

set(CMAKE_CXX_STANDARD 14)

add_executable(cyptography
        Base/main.cpp Base/Header/BASE.h Base/Realize/BASE.cpp Base/Realize/MD5.cpp Base/Header/MD5.h Base/Realize/AffineCipher.cpp Base/Header/AffineCipher.h Base/Header/Big.h Base/Realize/Big.cpp)
