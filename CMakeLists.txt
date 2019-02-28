cmake_minimum_required(VERSION 3.13)
project(cyptography)

set(CMAKE_CXX_STANDARD 14)

add_executable(cyptography
        Base/main.cpp Base/BASE.h Base/BASE.cpp Base/MD5.cpp Base/MD5.h Base/AffineCipher.cpp Base/AffineCipher.h)
