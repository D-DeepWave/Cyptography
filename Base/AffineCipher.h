//
// Created by DeepWave on 2019/2/28.
//

#ifndef CYPTOGRAPHY_AFFINECIPHER_H
#define CYPTOGRAPHY_AFFINECIPHER_H

#include <bits/stdc++.h>

using namespace std;

class AffineCipher {
public:
    int lenZ, lenC;

    string Z,C;
    vector<string> val;

    AffineCipher();

    AffineCipher(string z, string c);

    void Decode();

    int Find(string s);
};

int gcd(int a, int b);

void ExGCD(int a, int b, int &x, int &y);

#endif //CYPTOGRAPHY_AFFINECIPHER_H
