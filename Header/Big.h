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

const int Prime[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
int Big_Prime_Bits, Trial;
using namespace std;

ofstream file_out;
ofstream public_out;
ofstream private_out;

inline int sgn(int key);

class unsigned_BigInt {
public:
    int len;
    int __data[capacity];

    unsigned_BigInt() : len(0) {}

    unsigned_BigInt(const unsigned_BigInt &source);

    unsigned_BigInt(int key);

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

inline int compare(const unsigned_BigInt &A, const unsigned_BigInt &B);

inline void shift_right_base(unsigned_BigInt &A);

inline void shift_left_base(unsigned_BigInt &A);

inline void shift_right(unsigned_BigInt &A);

inline void shift_left(unsigned_BigInt &A);

inline void divide(const unsigned_BigInt &A, const unsigned_BigInt &B, unsigned_BigInt &Q, unsigned_BigInt &R);

unsigned_BigInt Minus_One;

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

ostream &operator<<(ostream &Out, const unsigned_BigInt &A);

ostream &operator<<(ostream &Out, const signed_BigInt &V);

bool operator==(const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator+(const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator-(const signed_BigInt &A);

signed_BigInt operator-(const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator*(const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator/(const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator%(const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt Euclid_GCD(const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt Extended_Euclid_GCD(const signed_BigInt &A, const signed_BigInt &B, signed_BigInt &X, signed_BigInt &Y);

output_BigInt operator+(const output_BigInt &A, const output_BigInt &B);

output_BigInt operator*(const output_BigInt &A, const int B);

BigInt_Exponentiation Get_Random_Binary(const int full, const int empty);

#endif //CYPTOGRAPHY_BIG_H
