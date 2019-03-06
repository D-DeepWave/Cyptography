//
// Created by Administrator on 2019/3/5.
//

#ifndef CYPTOGRAPHY_RSA_H
#define CYPTOGRAPHY_RSA_H


#include "Header/Big.h"

class RSA {
public:
    ofstream public_key_out;
    ofstream private_key_out;
    ifstream public_key_in;
    ifstream private_key_in;
    RSA(){}
    void GenerateKey(int bits, int round);
    unsigned_BigInt E_RSA(const char* s);
    void  D_RSA(unsigned_BigInt c);
};


#endif //CYPTOGRAPHY_RSA_H
