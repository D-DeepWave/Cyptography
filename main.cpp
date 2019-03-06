#include "Header/BASE.h"
#include "Header/MD5.h"
#include "Header/AffineCipher.h"
#include "Header/Big.h"
#include "Header/Elgamal.h"
#include "Header/RSA.h"
#include "windows.h"
#include "time.h"

Elgamal_sign e_s;
void Menu() {
    string args[10] = {"   USE BIG_INTEGER PRESS 1", "   USE MD5 PRESS 2", "   USE CIPHER PRESS 3",
                       "   USE RSA PRESS 4", "   USE ELGAMAL PRESS 5", "   EXIT PRESS 0"};
    cout << "           Menu" << endl;
    for (int i = 0; i < 6; i++) cout << args[i] << endl;
}

void BIG_INTEGER() {
//    char s[100];
//    scanf("%s", s);
//    Base64 a;
//     cout<<a.Encode((unsigned char*)s)<<endl;
//    cout << a.Decode(s) << endl;
    unsigned_BigInt a;
    cin >> a;
    cout << ToStringOut(a) << endl;
}

void CIPHER() {
//计算机学院网络工程信息安全，我们热爱中华人民共和国。大家
//和院程安我爱计
    cout << "Please Input Plaintext Space and Ciphertext Space" << endl;
    string a;
    string b;
    cin >> a >> b;
    AffineCipher x(a, b);
    x.Decode();
}

void MD5() {
    cout << "Please Input The Data" << endl;
    cout << "Press 1 to see the chinese example" << endl;
    class MD5 m;
    string s;
    cin >> s;
    if (s == "1")
        s = "中英文测试English123";
    cout << "The string is :" << s << endl;
    string res1 = m.GenerateMd5(s);
    string res2 = m.GenerateMd5(res1);
    string res3 = m.GenerateMd5(res2);
    cout << "md5: " << res1 << endl;
    cout << "md5(md5($pass)): " << res2 << endl;
    cout << "md5(md5(md5($pass))): " << res3 << endl;
}

void RSA() {
    class RSA a;
    cout << "      RSA   Menu" << endl;
    cout << "  Generate Key Press 1" << endl;
    cout << "  Encode Press 2" << endl;
    cout << "  Decode Press 3" << endl;
    int op, bits, round;
    char src[20];
    unsigned_BigInt s;
    cin >> op;
    if (op == 1) {
        cout << "Input bits and check round" << endl << "Your Choice is ";
        cin >> bits >> round;
        a.GenerateKey(bits, round);
    } else if (op == 2) {
        Base64 base64;
        char *res;
        unsigned_BigInt cipher;
        scanf("%s", src);
        cipher = a.E_RSA(src);
        cout << "The Cipher Text is " << cipher << "BASE 64 CODE is: ";
        cout << base64.Encode((unsigned char *) (ToStringOut(cipher).c_str())) << endl;
    } else if (op == 3) {
        cin >> s;
        a.D_RSA(s);
    }
}

void ELGAMAL() {
    class Elgamal a;
    cout << "    Elgamal  Menu" << endl;
    cout << "  Generate Key Press 1" << endl;
    cout << "  Encode Press 2" << endl;
    cout << "  Decode Press 3" << endl;
    cout << "  Elgamal Sign Press 4" << endl;
    cout << "  Elgamal Verification Press 5" << endl;
    int op;
    char src[20];
    unsigned_BigInt s;
    cin >> op;
    if (op == 1) {
        a.Generate(0);
    } else if (op == 2) {
        scanf("%s", src);
        cout << "The Cipher Text is " << endl;
        a.Encode(src);
    } else if (op == 3) {
        a.Decode();
    } else if (op == 4) {
        string name;
        cout << "Please Input your message!" << endl;
        cin >> name;
        class MD5 m;
        name = m.GenerateMd5(name);
        e_s.Sign(name);
    } else if (op == 5)
        e_s.Verification();
}


int main() {
    srand(time(0));
    int op_num, con = 1;
    Menu();
    while (con && cin >> op_num) {
        switch (op_num) {
            case 0:
                con = 0;
                break;
            case 1:
                BIG_INTEGER();
                break;
            case 2:
                MD5();
                break;
            case 3:
                CIPHER();
                break;
            case 4:
                RSA();
                break;
            case 5:
                ELGAMAL();
                break;
        }
        if (con) Menu();
    }
}

