//
// Created by Administrator on 2019/3/4.
//

#include "../Header/Elgamal.h"

Elgamal::Elgamal() {
    public_key_out.open("rsa_public.key", ios::trunc);
    private_key_out.open("rsa_private.key", ios::trunc);
    public_key_in.open("rsa_public.key");
    private_key_in.open("rsa_private.key");
}

unsigned_BigInt Get_Safe_Prime(int bits, int rnd) {
    while (true) {
        unsigned_BigInt q = Get_Prime(bits, rnd).data;
        unsigned_BigInt p = q * 2 + 1;
        BigInt_Exponentiation W;
        W.N = p;
        if (Miller_Rabin_Primality_Test(W, 3))
            return p;
    }
}

void Elgamal::Generate() {
    unsigned_BigInt q = Get_Safe_Prime(256, 3);
    unsigned_BigInt p = q * 2 + 1;
    unsigned_BigInt g;
    while (true) {
        unsigned_BigInt t = Get_Random_Binary(255, 200).N;
        if (compare(1, Modular_Exponentiation(t, t, p)) != 0 && compare(1, Modular_Exponentiation(t, q, p)) != 0) {
            g = t;
            break;
        }
    }
    unsigned_BigInt x = Get_Random_Binary(250, 200).N;
    unsigned_BigInt y = Modular_Exponentiation(g, x, p);
    K = Get_Random_Binary(250,200).N;
    Y = y;
    G = g;
    P = p;
    X = x;
}

string ToBin(wstring s)
{
    string res = "";
    wchar_t * t = const_cast<wchar_t *>(s.c_str());
    unsigned short * tt = (unsigned short*)t;
    for(int i = 0;i<s.length();i++)
    {
     bitset<16> a;
     a= *(tt+i);
     res+=a.to_string();
    }
    return res;
//    for(int i = 0;i<s.length();i++)
//        cout<<*(tt+i)<<endl;
//    wchar_t *p = (wchar_t*)tt;
//    wstring pp = p;
  //  wcout<<pp<<endl;
}

unsigned_BigInt BinToBig(string src)
{
    unsigned_BigInt res,b(1);
    for(int i = src.length()-1;i>=0;i--)
    {
        if(src[i]=='1')
            res=res+b;
        b = b*2;
    }
    return res;
}

wstring BigToWstring(unsigned_BigInt src)
{
    unsigned short res[256];
    int len = 0;
    while(compare(src,0)!=0)
    {
        unsigned_BigInt a = src % 65536;
        res[len++]=a.__data[0];
        src=src/65536;
    }
    wchar_t *p = (wchar_t*)res;
    wstring pp = p;
    return pp;
}

void Elgamal::Encode(wstring src)
{
    unsigned_BigInt m = BinToBig(ToBin(src));
    c1 = Modular_Exponentiation(G,K,P);
    c2 = m*Modular_Exponentiation(Y,K,P);
    cout<<"C1: "<<c1;
    cout<<"C2: "<<c2;
}

void Elgamal::Decode()
{
    unsigned_BigInt m ,temp;
   temp = Modular_Exponentiation(c1,X,P);
   signed_BigInt a,b,x,y;
   a.data = temp;
   b.data = P;
   Extended_Euclid_GCD(a,b,x,y);
   m = c2*x.data%P;
   wcout<<BigToWstring(m)<<endl;
}