//
// Created by DeepWave on 2019/3/1.
//

#ifndef CYPTOGRAPHY_BIG_H
#define CYPTOGRAPHY_BIG_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <random>

#define capacity 100
#define base 0x40000000
#define __base 0x20000000
#define base_bit 30
#define base_mod 0x3FFFFFFF
#define exponentiation_size 1500
#define unsignedZero unsigned_BigInt(0)
#define unsignedOne  unsigned_BigInt(1)
#define signedZero signed_BigInt(0)
#define signedOne  signed_BigInt(1)

using namespace std;

inline int sgn(int key) {
    if (key > 0) return 1;
    if (key < 0) return -1;
    if (key == 0) return 0;
}

class unsigned_BigInt {
public:
    int len;
    int __data[capacity];

    unsigned_BigInt() : len(0) {}

    unsigned_BigInt(const unsigned_BigInt &source);

    unsigned_BigInt(int key);

    unsigned_BigInt(string key);

    unsigned_BigInt &operator=(const unsigned_BigInt &key);

    int &operator[](int Index);

    int operator[](int Index) const;
};

struct signed_BigInt {
    unsigned_BigInt data;
    int sign;

    signed_BigInt() : data(0), sign(0) {}

    signed_BigInt(const signed_BigInt &source);

    signed_BigInt(int key) : sign(sgn(key)), data(abs(key)) {}

    signed_BigInt &operator=(const signed_BigInt &key);

    int &operator[](int Index) { return data[Index]; }

    int operator[](int Index) const { return data[Index]; }
};

struct output_BigInt {
    int len;
    int __data[capacity];

    output_BigInt() : len(0) {}

    output_BigInt(const output_BigInt &source);

    output_BigInt(int key);

    int &operator[](int Index) { return __data[Index]; }

    int operator[](int Index) const { return __data[Index]; }
};

struct BigInt_Exponentiation {
    unsigned_BigInt N;
    int len, valid;
    int data[exponentiation_size];

    BigInt_Exponentiation() : len(0) { memset(data, 0, sizeof(data)); }

    BigInt_Exponentiation(const BigInt_Exponentiation &source);

    int &operator[](int Index) { return data[Index]; }

    int operator[](int Index) const { return data[Index]; }
};

int compare(const unsigned_BigInt &A, const unsigned_BigInt &B);

void shift_right_base(unsigned_BigInt &A);

void shift_left_base(unsigned_BigInt &A);

void shift_right(unsigned_BigInt &A);

void shift_left(unsigned_BigInt &A);

void divide(const unsigned_BigInt &A, const unsigned_BigInt &B, unsigned_BigInt &Q, unsigned_BigInt &R);

unsigned_BigInt operator+(const unsigned_BigInt &A, const unsigned_BigInt &B);

unsigned_BigInt operator-(const unsigned_BigInt &A, const unsigned_BigInt &B);

unsigned_BigInt operator*(const unsigned_BigInt &A, const int B);

unsigned_BigInt operator*(const unsigned_BigInt &A, const unsigned_BigInt &B);

unsigned_BigInt operator/(const unsigned_BigInt &A, const int B);

unsigned_BigInt operator/(const unsigned_BigInt &A, const unsigned_BigInt &B);

unsigned_BigInt operator%(const unsigned_BigInt &A, const int B);

unsigned_BigInt operator%(const unsigned_BigInt &A, const unsigned_BigInt &B);

unsigned_BigInt Bin_To_Int(const BigInt_Exponentiation &W);

unsigned_BigInt Modular_Exponentiation(unsigned_BigInt A, const BigInt_Exponentiation &W);

unsigned_BigInt Modular_Exponentiation(unsigned_BigInt A, unsigned_BigInt B, const unsigned_BigInt &N);

istream &operator>>(istream &In, unsigned_BigInt &A);

ostream &operator<<(ostream &Out, const unsigned_BigInt &A);

ostream &operator<<(ostream &Out, const signed_BigInt &V);

ofstream &operator<<(ofstream &Out, const unsigned_BigInt &A);

bool operator==(const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator+(const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator-(const signed_BigInt &A);

signed_BigInt operator-(const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator*(const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator/(const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator%(const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt Get_Prime(const int Prime_Bits, const int Trial);

signed_BigInt Euclid_GCD(const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt Extended_Euclid_GCD(const signed_BigInt &A, const signed_BigInt &B, signed_BigInt &X, signed_BigInt &Y);

output_BigInt operator+(const output_BigInt &A, const output_BigInt &B);

output_BigInt operator*(const output_BigInt &A, const int B);

BigInt_Exponentiation Get_Random_Binary(const int full, const int empty);

bool Miller_Rabin_Witness(const unsigned_BigInt &A, const BigInt_Exponentiation &W);

bool Miller_Rabin_Primality_Test(const BigInt_Exponentiation &W, const int Trial);

void GenerateKey(int bits, int round);

unsigned_BigInt Encode(const string &X);

string Decode(unsigned_BigInt A);

unsigned_BigInt E_RSA(string s);

string D_RSA(unsigned_BigInt c) ;

#endif //CYPTOGRAPHY_BIG_H
