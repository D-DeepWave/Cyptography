//
// Created by Administrator on 2019/3/4.
//

#include "../Header/Elgamal.h"

Elgamal::Elgamal() {


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

void Elgamal::Generate(int level) {
    public_key_out.open("Elgamal_public.key", ios::trunc);
    private_key_out.open("Elgamal_private.key", ios::trunc);
    unsigned_BigInt q = Get_Safe_Prime(300, 3);
    unsigned_BigInt p = q * 2 + 1;
    unsigned_BigInt g;
    while (true) {
        unsigned_BigInt t = Get_Random_Binary(255, 100).N;
        if (compare(1, Modular_Exponentiation(t, t, p)) != 0 && compare(1, Modular_Exponentiation(t, q, p)) != 0) {
            g = t;
            break;
        }
    }
    unsigned_BigInt x = Get_Random_Binary(250, 100).N;
    unsigned_BigInt y = Modular_Exponentiation(g, x, p);

    cout << "Generate Successful!" << endl;
    cout << "Prime P is " << p;
    cout << "Y is " << y;
    cout << "G is " << g;

    public_key_out << p;
    public_key_out << y;
    public_key_out << g;
    if (level == 0)
        private_key_out << Get_Random_Binary(250, 100).N;
    else {
        while (true) {
            unsigned_BigInt k = Get_Random_Binary(250, 100).N;
            signed_BigInt a, b, xx, yy;
            a.sign = b.sign = 1;
            a.data = k;
            b.data = p - 1;
            if (Extended_Euclid_GCD(a, b, xx, yy) == signedOne) {
                private_key_out << k;
                break;
            }
        }
    }
    private_key_out << x;
}

Elgamal_key::Elgamal_key() {
    ifstream public_key_in;
    ifstream private_key_in;
    public_key_in.open("Elgamal_public.key");
    private_key_in.open("Elgamal_private.key");
    public_key_in >> P >> Y >> G;
    private_key_in >> K >> X;

}


void Elgamal::Encode(string src) {
    cipher_out.open("Elgamal_Cipher.txt", ios::app);
    public_key_in.open("Elgamal_public.key");
    private_key_in.open("Elgamal_private.key");
    unsigned_BigInt m = ToBig(src.c_str()), c1, c2, Y, G, K, P;
    public_key_in >> P >> Y >> G;
    private_key_in >> K;
    c1 = Modular_Exponentiation(G, K, P);
    c2 = m * Modular_Exponentiation(Y, K, P);
    c2 = c2 % P;
    cout << "C1: " << c1;
    cout << "C2: " << c2;
    cipher_out << c1 << c2;
}

void Elgamal::Decode() {
    cipher_in.open("Elgamal_Cipher.txt");
    public_key_in.open("Elgamal_public.key");
    private_key_in.open("Elgamal_private.key");
    unsigned_BigInt m, temp, c1, c2, X, P;
    cipher_in >> c1 >> c2;
    private_key_in >> temp >> X;
    public_key_in >> P;
    temp = Modular_Exponentiation(c1, X, P);
    signed_BigInt a, b, x, y;
    a.sign = b.sign = 1;
    a.data = temp;
    b.data = P;
    Extended_Euclid_GCD(a, b, x, y);
    if (x.sign == -1) x = x + b;
    m = (c2 * x.data) % P;
    cout << "Decode The Number " << m;
    printf("%s\n", ToChar(m));
}

Elgamal_sign::Elgamal_sign() {
    m = r = s = 0;
}

void Elgamal_sign::Sign(string src) {
    e.Generate(1);
    Elgamal_key k;
    r = Modular_Exponentiation(k.G, k.K, k.P);
    m = ToBig(src.c_str());
//m = 14;
    signed_BigInt a, b, x, y, temp, M, R, XX;

    a.sign = b.sign = M.sign = R.sign = XX.sign = 1;
    a.data = k.K;
    b.data = k.P - unsignedOne;
    Extended_Euclid_GCD(a, b, x, y); //x->k_inv
    if (x.sign == -1) x = x + b;

    M.data = m;R.data=r;XX.data = k.X;;
    temp = x * (M-R*XX)%b;
    if(temp.sign==-1) temp = b + temp;
    s = temp.data;
   cout<<"This is Sign Message(m,r,s)"<<endl;
   cout<<"m: "<<m<<"r: "<<r<<"s: "<<s;
}

void Elgamal_sign::Verification() {
    Elgamal_key k;
    unsigned_BigInt left, right;
    left = (Modular_Exponentiation(k.Y, r, k.P) * Modular_Exponentiation(r, s, k.P)) % k.P;
    //cout<<"LLLL:"<<k.Y<<r<<s;
    right = Modular_Exponentiation(k.G, m, k.P);
    cout << "Left:" << left << "Right:" << right;
    if (compare(left, right) == 0)
        cout << "This sign is Correct!" << endl;
    else
        cout << "Verification faild!" << endl;
}

