//
// Created by DeepWave on 2019/2/28.
//

#include "../Header/AffineCipher.h"

AffineCipher::AffineCipher(string z, string c) {
    Z = z;
    C = c;
    lenZ = Z.length() / 2;
    lenC = C.length() / 2;
    for (int i = 0; i < Z.length(); i += 2)
        val.push_back(z.substr(i, 2));
}

int AffineCipher::Find(string s) {
    for(int i = 0;i<lenZ;i++)
    {
        if(s==val[i]) return i;
    }
    return lenZ;
}

void AffineCipher::Decode() {
    for (int i = 2, j; i < lenZ; i++) {
        if (gcd(i, lenZ) == 1) {
            int x, y, inv;
            ExGCD(i, lenZ, x, y);
            inv = (x + lenZ) % lenZ;
            for (j = 0; j < lenZ; j++) {
                cout << "Now is a = " << i << " and b = " << j << "    ";
                for (int u = 0; u < lenC; u++) {
                    string temp = C.substr(u*2,2);
                    int c = Find(temp);
                    int pos = inv * (c - j + lenZ) % lenZ;
                    cout << val[pos];
                }
                cout << endl;
            }
        }
    }
}

void ExGCD(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1;
        y = 0;
        return;
    }
    ExGCD(b, a % b, y, x);
    int c = a / b;
    c = c * x;
    y = y - c;
}

int gcd(int a, int b) {
    if (!b)
        return a;
    return gcd(b, a % b);
}
