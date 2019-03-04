//
// Created by Administrator on 2019/3/4.
//

#ifndef CYPTOGRAPHY_ELGAMAL_H
#define CYPTOGRAPHY_ELGAMAL_H

#include "Big.h"
#include <cstdlib>
#include <memory>
#include <string>
#include <bitset>

class Elgamal {
public:
    ofstream public_key_out;
    ofstream private_key_out;
    ifstream public_key_in;
    ifstream private_key_in;
    unsigned_BigInt P, Y, G, X, K,c1,c2;

    Elgamal();

    void Generate();

    void Encode(wstring src);

    void Decode();
};

string ToBin(wstring s);

unsigned_BigInt BinToBig(string src);

wstring BigToWstring(unsigned_BigInt src);

#endif //CYPTOGRAPHY_ELGAMAL_H
