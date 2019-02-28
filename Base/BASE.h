//
// Created by DeepWave on 2019/2/25.
//


#ifndef BASE_BASE_H
#define BASE_BASE_H
#define MAX_LEN 2048
#define ZERO BigInteger(0)
#define ONE BigInteger(1)
#include<bits/stdc++.h>
using namespace std;
class BigInteger
{
public:
    int val[MAX_LEN],len;
    int flag;
    BigInteger(string s);
    BigInteger(int s);
    BigInteger();
};
ostream& operator <<(ostream &out,BigInteger &a);
int Compare(BigInteger a,BigInteger b);
BigInteger operator +( BigInteger a, BigInteger b);
BigInteger operator -( BigInteger a, BigInteger b);
BigInteger operator *(BigInteger &a, BigInteger &b);
BigInteger operator /(BigInteger a, BigInteger b);
BigInteger operator %(const BigInteger &a, int b);
BigInteger operator %(BigInteger a, BigInteger b);
BigInteger ShiftLeft(BigInteger &a,int b);
BigInteger ShiftRight(BigInteger &a,int b);
BigInteger SubBig(BigInteger a,int s,int e);
BigInteger Karatsuba(BigInteger a,BigInteger b);
BigInteger ModPow(BigInteger a,BigInteger b,BigInteger mod);
BigInteger ModMul(BigInteger a,BigInteger b,BigInteger mod);
BigInteger GCD(BigInteger a,BigInteger b);
void ExGCD(BigInteger a,BigInteger b,BigInteger &x,BigInteger &y);
BigInteger Inv(BigInteger a,BigInteger b);
BigInteger GetPrime();
bool MillerRabin(BigInteger n);
bool IsEqual(BigInteger a,BigInteger b);
#endif //BASE_BASE_H

