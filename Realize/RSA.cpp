//
// Created by Administrator on 2019/3/5.
//

#include "RSA.h"



void RSA::GenerateKey(int bits, int round) {
    public_key_out.open("rsa_public.key", ios::app);
    private_key_out.open("rsa_private.key", ios::app);
    signed_BigInt P = Get_Prime(bits, round);
    signed_BigInt Q = Get_Prime(bits, round);
    signed_BigInt N = P * Q;
    signed_BigInt Phi = (P - 1) * (Q - 1);
    signed_BigInt D, E, Y;
    for (E = 5; !(Extended_Euclid_GCD(E, Phi, D, Y) == signedOne); E = E + 2);
    if (D.sign == -1)
        D = D + Phi;
    cout << "P = :" << P;
    cout << "Q = :" << Q;
    cout << "N = :" << N;
    cout << "E = :" << E;
    cout << "D = :" << D;

    private_key_out << D ;
    private_key_out << P ;
    private_key_out << Q ;
    public_key_out << N ;
    public_key_out << E ;
}


unsigned_BigInt RSA::E_RSA(const char* s) {
    public_key_in.open("rsa_public.key");
    private_key_in.open("rsa_private.key");
    unsigned_BigInt res, m, e, n;
    m = ToBig(s);
    public_key_in >> n>>e ;
    //  cout<<m<<n<<e;
    res = Modular_Exponentiation(m, e, n);
    return res;
}

void RSA::D_RSA(unsigned_BigInt c) {
    public_key_in.open("rsa_public.key");
    private_key_in.open("rsa_private.key");
    unsigned_BigInt res, d, n;
    char* s;
    public_key_in >> n;
    private_key_in >> d;
    cout<<n<<d;
    res = Modular_Exponentiation(c, d, n);
   // cout<<res;
    s = ToChar(res);
    printf("The Text is :%s\n",s);
}
