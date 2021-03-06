#include <time.h>
#include "../Header/Big.h"

//
// Created by DeepWave on 2019/3/1.
//
unsigned_BigInt Minus_One;
int Big_Prime_Bits, Trial;
const int Prime[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

unsigned_BigInt::unsigned_BigInt(const unsigned_BigInt &source) : len(source.len) {
    memcpy(__data, source.__data, len * sizeof *__data);
}

unsigned_BigInt::unsigned_BigInt(int key) : len(0) {
    for (; key > 0; key >>= base_bit)
        __data[len++] = key & base_mod;
}

unsigned_BigInt::unsigned_BigInt(string key) {
    unsigned_BigInt res;
    for (int i = 0; i < key.length(); i++)
        res = res * 10 + key[i] - '0';
    len = res.len;
    memcpy(__data, res.__data, len * sizeof *__data);
}

unsigned_BigInt &unsigned_BigInt::operator=(const unsigned_BigInt &key) {
    len = key.len;
    memcpy(__data, key.__data, len * sizeof *__data);
    return *this;
}

int &unsigned_BigInt::operator[](int Index) {
    return __data[Index];
}

int unsigned_BigInt::operator[](int Index) const {
    return __data[Index];
}

inline int compare(const unsigned_BigInt &A, const unsigned_BigInt &B) {
    if (A.len != B.len) return A.len > B.len ? 1 : -1;
    int i;
    for (i = A.len - 1; i >= 0 && A[i] == B[i]; --i);
    if (i < 0) return 0;
    return A[i] > B[i] ? 1 : -1;
}

inline void shift_right_base(unsigned_BigInt &A) {
    if (A.len == 0) return;
    for (int i = 0; i < A.len - 1; ++i)
        A[i] = A[i + 1];
    --A.len;
}

inline void shift_left_base(unsigned_BigInt &A) {
    if (A.len == 0) return;
    for (int i = A.len; i > 0; --i)
        A[i] = A[i - 1];
    A[0] = 0;
    ++A.len;
}

inline void shift_right(unsigned_BigInt &A) {
    if (A.len == 0) return;
    for (int i = 0; i < A.len - 1; ++i) {
        A[i] = (A[i] >> 1);
        if ((A[i + 1] & 1) == 1)
            A[i] = A[i] | __base;
    }
    A[A.len - 1] = A[A.len - 1] >> 1;
    if (A[A.len - 1] == 0) --A.len;
}

inline void shift_left(unsigned_BigInt &A) {
    if (A.len == 0) return;
    int k = A.len;
    if ((A[A.len - 1] & __base) != 0)
        A[A.len++] = 1;
    for (int i = k - 1; i > 0; --i) {
        A[i] = (A[i] << 1) & base_mod;
        if ((A[i - 1] & __base) != 0)
            ++A[i];
    }
    A[0] = (A[0] << 1) & base_mod;
}

unsigned_BigInt operator+(const unsigned_BigInt &A, const unsigned_BigInt &B) {
    unsigned_BigInt R;
    int i;
    int Carry = 0;
    for (i = 0; i < A.len || i < B.len || Carry > 0; ++i) {
        if (i < A.len) Carry += A[i];
        if (i < B.len) Carry += B[i];
        R[i] = Carry & base_mod;
        Carry >>= base_bit;
    }
    R.len = i;
    return R;

}

unsigned_BigInt operator-(const unsigned_BigInt &A, const unsigned_BigInt &B) {
    unsigned_BigInt R;
    int Carry = 0;
    R.len = A.len;
    for (int i = 0; i < R.len; ++i) {
        R[i] = A[i] - Carry;
        if (i < B.len) R[i] -= B[i];
        if (R[i] < 0) Carry = 1, R[i] += base;
        else Carry = 0;
    }
    while (R.len > 0 && R[R.len - 1] == 0) --R.len;
    return R;
}

unsigned_BigInt operator*(const unsigned_BigInt &A, const int B) {
    int i;
    if (B == 0) return 0;
    unsigned_BigInt R;
    long long Carry = 0;
    for (i = 0; i < A.len || Carry > 0; ++i) {
        if (i < A.len) Carry += (long long) (A[i]) * B;
        R[i] = Carry & base_mod;
        Carry >>= base_bit;
    }
    R.len = i;
    return R;
}

unsigned_BigInt operator*(const unsigned_BigInt &A, const unsigned_BigInt &B) {
    if (B.len == 0) return 0;
    unsigned_BigInt R;
    for (int i = 0; i < A.len; ++i) {
        long long Carry = 0;
        for (int j = 0; j < B.len || Carry > 0; ++j) {
            if (j < B.len) Carry += (long long) (A[i]) * B[j];
            if (i + j < R.len) Carry += R[i + j];
            if (i + j >= R.len) R[R.len++] = Carry & base_mod;
            else R[i + j] = Carry & base_mod;
            Carry >>= base_bit;
        }
    }
    return R;
}


unsigned_BigInt operator/(const unsigned_BigInt &A, const int B) {

    unsigned_BigInt R;
    long long C = 0;
    for (int i = A.len - 1; i >= 0; --i) {
        C = (C << base_bit) + A[i];
        R[i] = C / B;
        C %= B;
    }
    R.len = A.len;
    while (R.len > 0 && R[R.len - 1] == 0) --R.len;
    return R;

}

unsigned_BigInt operator/(const unsigned_BigInt &A, const unsigned_BigInt &B) {
    if (compare(A, B) < 0) return 0;
    unsigned_BigInt R, Carry = 0;
    int left, right, mid;
    for (int i = A.len - 1; i >= 0; --i) {
        shift_left_base(Carry);
        Carry = Carry + A[i];
        left = 0;
        right = base;
        while (left + 1 < right) {
            mid = (left + right) >> 1;
            if (compare(B * mid, Carry) <= 0)
                left = mid;
            else
                right = mid;
        }
        R[i] = left;
        Carry = Carry - B * left;
    }
    R.len = A.len;
    while (R.len > 0 && R[R.len - 1] == 0) --R.len;
    return R;
}

unsigned_BigInt operator%(const unsigned_BigInt &A, const int B) {
    long long C = 0;
    for (int i = A.len - 1; i >= 0; --i) {
        C = (C << base_bit) + A[i];
        C %= B;
    }
    return C;
}

unsigned_BigInt operator%(const unsigned_BigInt &A, const unsigned_BigInt &B) {
    if (compare(A, B) < 0) return A;
    unsigned_BigInt Carry = 0;
    int left, right, mid;
    for (int i = A.len - 1; i >= 0; --i) {
        shift_left_base(Carry);
        Carry = Carry + A[i];
        left = 0;
        right = base;
        while (left + 1 < right) {
            mid = (left + right) >> 1;
            if (compare(B * mid, Carry) <= 0)
                left = mid;
            else
                right = mid;
        }
        Carry = Carry - B * left;
    }
    return Carry;
}

istream &operator>>(istream &In, unsigned_BigInt &A) {
    char ch;
    for (A = 0; In >> ch;) {
        A = A * 10 + (ch - '0');
        if (In.peek() <= ' ') break;
    }
    return In;
}

ifstream &operator>>(ifstream &In, unsigned_BigInt &A) {
    char ch;
    for (A = 0; In >> ch;) {
        A = A * 10 + (ch - '0');
        if (In.peek() <= ' ') break;
    }
    return In;
}

inline void divide(const unsigned_BigInt &A, const unsigned_BigInt &B, unsigned_BigInt &Q, unsigned_BigInt &R) {
    static bool flag[exponentiation_size];
    static int top;
    static unsigned_BigInt temp_divide;

    temp_divide = A;
    for (top = 0; compare(temp_divide, B) >= 0; ++top) {
        flag[top] = ((temp_divide[0] & 1) == 1);
        shift_right(temp_divide);
    }
    Q = 0;
    R = temp_divide;
    for (int i = top - 1; i >= 0; --i) {
        shift_left(Q);
        shift_left(R);
        if (flag[i])
            R = R + 1;
        if (compare(R, B) >= 0) {
            R = R - B;
            Q = Q + 1;
        }
    }
}

signed_BigInt::signed_BigInt(const signed_BigInt &source) : sign(source.sign) {
    data = source.data;
}

signed_BigInt &signed_BigInt::operator=(const signed_BigInt &key) {
    sign = key.sign;
    data = key.data;
    return *this;
}

output_BigInt::output_BigInt(const output_BigInt &source) : len(source.len) {
    memcpy(__data, source.__data, len * sizeof *__data);
}

output_BigInt::output_BigInt(int key) : len(0) {
    for (; key > 0; key /= 1000000000)
        __data[len++] = key % 1000000000;
}

output_BigInt operator+(const output_BigInt &A, const output_BigInt &B) {
    output_BigInt R;
    int i;
    int Carry = 0;
    for (i = 0; i < A.len || i < B.len || Carry > 0; ++i) {
        if (i < A.len) Carry += A[i];
        if (i < B.len) Carry += B[i];
        R[i] = Carry % 1000000000;
        Carry /= 1000000000;
    }
    R.len = i;
    return R;
}

output_BigInt operator*(const output_BigInt &A, const int B) {
    int i;
    if (B == 0) return 0;
    output_BigInt R;
    long long Carry = 0;
    for (i = 0; i < A.len || Carry > 0; ++i) {
        if (i < A.len) Carry += (long long) (A[i]) * B;
        R[i] = Carry % 1000000000;
        Carry /= 1000000000;
    }
    R.len = i;
    return R;
}

ostream &operator<<(ostream &Out, const unsigned_BigInt &A) {
    if (A.len == 0) {
        Out << 0;
        return Out;
    }

    output_BigInt V = 0;
    for (int i = A.len - 1; i >= 0; --i)
        V = V * base + A[i];


    Out << V[V.len - 1];
    for (int i = V.len - 2; i >= 0; --i)
        for (int j = 100000000; j > 0; j /= 10)
            Out << V[i] / j % 10;
    Out << endl;


    int digit = 0;
    for (int k = 1; k <= V[V.len - 1]; k *= 10)
        ++digit;

    digit += (V.len - 1) * 9;

    //  Out << "Total Digit = " << digit << endl;

    return Out;
}

ofstream &operator<<(ofstream &Out, const unsigned_BigInt &A) {
    if (A.len == 0) {
        Out << "0";
        return Out;
    }

    output_BigInt V = 0;
    for (int i = A.len - 1; i >= 0; --i)
        V = V * base + A[i];

    char c[100];
    sprintf(c, "%d", V[V.len - 1]);
    Out << c;
    for (int i = V.len - 2; i >= 0; --i)
        for (int j = 100000000; j > 0; j /= 10) {
            sprintf(c, "%d", V[i] / j % 10);
            Out << c;
        }
    Out << endl;

    return Out;
}

ostream &operator<<(ostream &Out, const signed_BigInt &V) {
    string c = (V.sign == -1) ? "-" : "";
    Out << c << V.data;
    return Out;
}

bool operator==(const signed_BigInt &A, const signed_BigInt &B) {
    if (A.sign != B.sign) return false;
    return (compare(A.data, B.data) == 0);
}

signed_BigInt operator+(const signed_BigInt &A, const signed_BigInt &B) {
    if (A.sign == 0) return B;
    if (B.sign == 0) return A;
    signed_BigInt R;
    if (A.sign * B.sign == 1) {
        R.data = A.data + B.data;
        R.sign = A.sign;
    } else if (A.sign == 1) {
        int k = compare(A.data, B.data);
        if (k == 1) {
            R.sign = 1;
            R.data = A.data - B.data;
        } else if (k == 0) {
            R.sign = 0;
            R.data = 0;
        } else if (k == -1) {
            R.sign = -1;
            R.data = B.data - A.data;
        }
    } else {
        int k = compare(B.data, A.data);
        if (k == 1) {
            R.sign = 1;
            R.data = B.data - A.data;
        } else if (k == 0) {
            R.sign = 0;
            R.data = 0;
        } else if (k == -1) {
            R.sign = -1;
            R.data = A.data - B.data;
        }
    }
    return R;
}

signed_BigInt operator-(const signed_BigInt &A) {
    signed_BigInt R;
    R.sign = -A.sign;
    R.data = A.data;
    return R;
}

signed_BigInt operator-(const signed_BigInt &A, const signed_BigInt &B) {
    if (B.sign == 0) return A;
    if (A.sign == 0) return -B;
    signed_BigInt R;
    if (A.sign * B.sign == -1) {
        R.sign = A.sign;
        R.data = A.data + B.data;
    } else {
        int k = compare(A.data, B.data);
        if (k == 0) {
            R.sign = 0;
            R.data = 0;
            return R;
        }
        if (A.sign == 1 && B.sign == 1) {
            if (k == -1) {
                R.data = B.data - A.data;
                R.sign = -1;
            } else {
                R.data = A.data - B.data;
                R.sign = 1;
            }
        } else {
            if (k == -1) {
                R.data = B.data - A.data;
                R.sign = 1;
            } else {
                R.data = A.data - B.data;
                R.sign = -1;
            }
        }
    }
    return R;
}

signed_BigInt operator*(const signed_BigInt &A, const signed_BigInt &B) {
    signed_BigInt R;
    if (A.sign * B.sign == 0) {
        R.data = 0;
        R.sign = 0;
        return R;
    }
    R.data = A.data * B.data;
    R.sign = A.sign * B.sign;
    return R;
}

signed_BigInt operator/(const signed_BigInt &A, const signed_BigInt &B) {
    signed_BigInt R;
    if (A.sign == 0) {
        R.data = 0;
        R.sign = 0;
        return R;
    }
    R.data = A.data / B.data;
    if (R.data.len == 0)
        R.sign = 0;
    else
        R.sign = A.sign * B.sign;
    return R;
}

signed_BigInt operator%(const signed_BigInt &A, const signed_BigInt &B) {
    signed_BigInt R;
    if (A.sign == 0) {
        R.data = 0;
        R.sign = 0;
        return R;
    }
    R.data = A.data % B.data;
    if (R.data.len == 0) {
        R.sign = 0;
        return R;
    }
    R.sign = 1;
    if (A.sign * B.sign == -1)
        R.data = B.data - A.data % B.data;
    return R;
}

signed_BigInt Euclid_GCD(const signed_BigInt &A, const signed_BigInt &B) {
    return (B.sign == 0) ? A : Euclid_GCD(B, A % B);
}

signed_BigInt Extended_Euclid_GCD( signed_BigInt A,signed_BigInt B, signed_BigInt &X, signed_BigInt &Y) {
    if (B.sign == 0) {
        X = 1, Y = 0;
        return A;
    }
    signed_BigInt r, q, s1 = 1, s2 = 0;
    X = 0;Y =1;
    r = A%B;
    q = A/B;
    while(compare(r.data,0)!=0)
    {
        signed_BigInt m =X,n = Y;
        X = s1-X*q;
        Y = s2-Y*q;
        s1 = m;s2 = n;
        A = B;B = r;
        q = A /B;
        r = A%B;
    }
    return B;
}

BigInt_Exponentiation::BigInt_Exponentiation(const BigInt_Exponentiation &source) : len(source.len) {
    memcpy(data, source.data, len * sizeof *data);
}

unsigned_BigInt Bin_To_Int(const BigInt_Exponentiation &W) {
    unsigned_BigInt R;
    R.len = 0;
    int i, k;
    for (i = 0; i + base_bit < W.len; i += base_bit) {
        k = 0;
        for (int j = base_bit - 1; j >= 0; --j)
            k = (k << 1) + W[i + j];
        R[R.len++] = k;
    }
    if (i < W.len) {
        k = 0;
        for (int j = W.len - 1; j >= i; --j)
            k = (k << 1) + W[j];
        R[R.len++] = k;
    }
    return R;
}

unsigned_BigInt Modular_Exponentiation(unsigned_BigInt A, const BigInt_Exponentiation &W) {
    unsigned_BigInt R = 1;
    for (int i = W.valid; i < W.len; ++i) {
        if (W[i] == 1)
            R = (R * A) % W.N;
        A = (A * A) % W.N;
    }
    return R;
}

unsigned_BigInt Modular_Exponentiation(unsigned_BigInt A, unsigned_BigInt B, const unsigned_BigInt &N) {
    unsigned_BigInt R = 1;
    while (B.len != 0) {
        if ((B[0] & 1) == 1)
            R = (R * A) % N;
        A = (A * A) % N;
        shift_right(B);
    }
    return R;
}

BigInt_Exponentiation Get_Random_Binary(const int full, const int empty) {
    //cout << "NOW :" << time(0) << endl;
    BigInt_Exponentiation X;
    X.len = full + empty;
    X.valid = empty;  // Start from empty
    X[0] = X[empty] = 1;
    for (int i = empty + 1; i < X.len - 1; ++i)
        X[i] = (rand() & 1);
    X[X.len - 1] = 1;
    X.N = Bin_To_Int(X);
    return X;
}

bool Miller_Rabin_Witness(const unsigned_BigInt &A, const BigInt_Exponentiation &W) {
    int t = W.valid;
    unsigned_BigInt X[2];
    X[0] = Modular_Exponentiation(A, W);
    for (int i = 1; i <= t; ++i) {
        X[i & 1] = (X[(i - 1) & 1] * X[(i - 1) & 1]) % W.N;
        if (compare(X[i & 1], unsignedOne) == 0 && compare(X[(i - 1) & 1], unsignedOne) != 0 &&
            compare(X[(i - 1) & 1], Minus_One) != 0)
            return true;
    }
    if (compare(X[t & 1], unsignedOne) != 0)
        return true;
    return false;
}

bool Miller_Rabin_Primality_Test(const BigInt_Exponentiation &W, const int Trial) {
    for (int i = 0; i < 25; ++i)
        if ((W.N % Prime[i]).len == 0) return false;
    Minus_One = W.N - 1;
    unsigned_BigInt A;
    if (Miller_Rabin_Witness(2, W)) return false;
    for (int i = 1; i < Trial; ++i) {
        A = Get_Random_Binary(W.len - 2, 1).N;
        if (Miller_Rabin_Witness(A, W)) return false;
    }
    return true;
}

signed_BigInt Get_Prime(const int Prime_Bits, const int Trial) {
    int delta = rand() % (Prime_Bits / 20) + 1;
    int bits = Prime_Bits + delta;
    int noisy = rand() % 100 + 100;
    int counter = 0;
    BigInt_Exponentiation W;

//   cin>>W.N;

    // W.N = W.N-100;
    while (true) {
        ++counter;
        W = Get_Random_Binary(bits - noisy, noisy);
        // empty >= 1
        // cout << counter << endl;
//        cout << W.N;
        bool f;
        f = Miller_Rabin_Primality_Test(W, Trial);
//        cout<<counter<<" is "<<f<<endl;
        if (f) {
            cout << "Total Trial = " << counter << endl;
            signed_BigInt R;
            R.sign = 1;
            R.data = W.N;
            //cout << "Yes it's Prime" << endl;
            return R;
        }
        //  cout << "It is not Prime!" << endl;
//       W.N = W.N + 2;
    }
}

unsigned_BigInt ToBig(const char *src) {
    unsigned_BigInt res(0);
    int len = 0;
    for (; *(src + len) != '\0';) {
        int temp = (int) *(src + len);
        if (temp < 0) temp = 10000 + abs(temp);
        //cout<<temp<<endl;
        res.__data[len++] = temp;
    }
    res.len = len;
    cout << "The char has convert to:" << res;
    return res;
}

char *ToChar(unsigned_BigInt src) {
    unsigned_BigInt base_max("4294967296");
    char *res = new char[128];
    for (int i = 0; i < src.len; i++) {
        // cout <<src.__data[i] << endl;
        int temp = src.__data[i];
        if (temp > 10000) temp = -(temp - 10000);
        res[i] = (char) temp;
    }
    res[src.len] = '\0';
    // printf("%s\n",res);
    return res;
}

string ToStringOut(unsigned_BigInt src) {
    if (src.len == 0) return 0;
    string res = "";
    output_BigInt V = 0;
    for (int i = src.len - 1; i >= 0; --i)
        V = V * base + src[i];
    char *c;
    sprintf(c, "%d", V[V.len - 1]);
    res += c;
    for (int i = V.len - 2; i >= 0; --i)
        for (int j = 100000000; j > 0; j /= 10) {
            sprintf(c, "%d", V[i] / j % 10);
            res += c;
        }
    return res;
}
