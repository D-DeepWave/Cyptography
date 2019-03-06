//
// Created by Administrator on 2019/3/4.
//

#ifndef CYPTOGRAPHY_ELGAMAL_H
#define CYPTOGRAPHY_ELGAMAL_H

#include "Big.h"
#include <cstdlib>
#include <memory>
#include <bitset>
#include <fstream>
#include <iostream>
#include <string>


class Elgamal {
public:
    ofstream public_key_out;
    ofstream private_key_out;
    ofstream cipher_out;
    ifstream cipher_in;
    ifstream public_key_in;
    ifstream private_key_in;

    Elgamal();

    void Generate(int level);

    void Encode(string src);

    void Decode();

};

class Elgamal_sign
{
public:
    unsigned_BigInt m,r,s;
    Elgamal e;
    Elgamal_sign();
    void Sign(string s);
    void Verification();
};

class Elgamal_key
{
public:
    unsigned_BigInt Y,G,P,K,X;
    Elgamal_key();
};

#endif //CYPTOGRAPHY_ELGAMAL_H
