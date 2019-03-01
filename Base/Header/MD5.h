//
// Created by DeepWave on 2019/2/27.
//

#ifndef CYPTOGRAPHY_MD5_H
#define CYPTOGRAPHY_MD5_H
#define UI unsigned int
#define BLOCK_LEN 512
#define BYTE_LEN 8
#define BLOCK_FILL_MAX 448
#define KA 0x67452301
#define KB 0xefcdab89
#define KC 0x98badcfe
#define KD 0x10325476
#define B 4294967296
#define F(X, Y, Z) (((X) & (Y)) | ((~X) & (Z)))
#define G(X, Y, Z) (((X) & (Z)) | ((Y) & (~Z)))
#define H(X, Y, Z) ((X) ^ (Y) ^ (Z))
#define I(X, Y, Z) ((Y) ^ ((X) | (~Z)))


#include<bits/stdc++.h>

using namespace std;
const char h[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

class MD5 {
public:
    UI ua, ub, uc, ud;

    MD5();

    string GenerateMd5(string s);

    void TurnOperation(unsigned char *src);
};

int FillData(string s, unsigned char *output[]);

UI ShiftLeft(UI src, int n);

string ToHex(unsigned int n);

#endif //CYPTOGRAPHY_MD5_H
