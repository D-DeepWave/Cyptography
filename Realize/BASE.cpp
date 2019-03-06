//
// Created by DeepWave on 2019/2/25.
//

#include"../Header/BASE.h"

int prime[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};


BigInteger::BigInteger() {
    memset(val, 0, sizeof(val));
    len = 0;
    flag = 1;
}

BigInteger::BigInteger(string s) {
    memset(val, 0, sizeof(val));
    len = 0;
    for (int i = s.length() - 1; i >= 0; i--)
        val[len++] = s[i] - '0';
    flag = 1;
}

BigInteger::BigInteger(int s) {
    memset(val, 0, sizeof(val));
    len = 0;
    while (s) {
        val[len++] = s % 10;
        s /= 10;
    }
    flag = 1;
}

int Compare(BigInteger a, BigInteger b) {
    if (a.flag != b.flag)
        return a.flag > b.flag;

    for (int i = a.len - 1; i >= 0; i--, a.len--)
        if (a.val[i]) break;
    for (int i = b.len - 1; i >= 0 && b.val[i]; i--, b.len--)
        if (b.val[i]) break;
    if (a.len != b.len)
        return a.len > b.len;
    else {
        for (int i = a.len - 1; i >= 0; i--)
            if (a.val[i] != b.val[i])
                return a.val[i] > b.val[i];
    }
    return 2;
}

bool IsEqual(BigInteger a, BigInteger b) {
    for (int i = a.len - 1; i >= 0; i--, a.len--)
        if (a.val[i]) break;
    for (int i = b.len - 1; i >= 0 && b.val[i]; i--, b.len--)
        if (b.val[i]) break;
    if (a.len != b.len) return false;
    for (int i = 0; i < a.len; i++) {
        if (a.val[i] != b.val[i])
            return false;
    }
    return true;
}

BigInteger ShiftLeft(BigInteger &a, int b) {
    if (a.len == 0) return 0;
    for (int i = a.len - 1; i >= 0; i--, a.len--)
        if (a.val[i]) break;
    for (int i = a.len - 1; i >= 0; i--) {
        int x = i + b;
        a.val[x] = a.val[i];
    }
    for (int i = 0; i < b; i++) a.val[i] = 0;
    a.len += b;
}

BigInteger ShiftRight(BigInteger &a, int b) {
    if (a.len == 0) return 0;
    for (int i = 0; i < a.len; i++) {
        int x = i + b;
        a.val[i] = a.val[x];
    }
    for (int i = 0; i < b; i++)
        a.val[a.len + b - 1] = 0;
    a.len -= b;
}

BigInteger SubBig(BigInteger a, int s, int l) {
    BigInteger res;
    res.len = 0;
    for (int i = s; i < s + l; i++)
        res.val[res.len++] = a.val[i];
    return res;
}

BigInteger Karatsuba(BigInteger a, BigInteger b) {
    int mid, len = max(a.len, b.len);
    if (len == 0)
        return 0;
    if (len == 1)
        return a.val[0] * b.val[0];
    mid = len / 2;
    BigInteger x1 = SubBig(a, 0, len - mid);  //low
    BigInteger x2 = SubBig(a, len - mid, mid);  //high
    BigInteger y1 = SubBig(b, 0, len - mid);
    BigInteger y2 = SubBig(b, len - mid, mid);
    BigInteger z0 = Karatsuba(x1, y1);  //bd
    BigInteger z1 = Karatsuba(x1 + x2, y1 + y2); //(a+b)*(c+d)
    BigInteger z2 = Karatsuba(x2, y2);  //ac
    //cout<<z0<<z1<<z2;
    BigInteger r1 = z2, r2 = z1;
    //cout<<"start:"<<r2;
    r2 = r2 - z0;
    // cout<<"r2:"<<r2<<"z2"<<z2;
    r2 = r2 - z2;
    //cout<<r2<<endl;
    ShiftLeft(r1, 2 * (len - mid));
    ShiftLeft(r2, len - mid);
    //cout<<r1<<r2<<z0<<endl;
    return r1 + r2 + z0;
}

ostream &operator<<(ostream &out, BigInteger &a) {

    if (a.len == 0)
        out << 0;
    else
        for (int i = a.len - 1; i >= 0; i--)
            out << a.val[i];
    out << endl;
    return out;
}

BigInteger operator%(const BigInteger &a, int b) {
    int res;
    for (int i = a.len - 1; i >= 0; i--)
        res = (res * 10 + a.val[i]) % b;
    return (res + b) % b;
}

BigInteger operator%(BigInteger a, BigInteger b) {
    int pos = a.len - b.len, C = Compare(a, b);
    if (C == 2) return 0;
    if (C == 0) return a;
    ShiftLeft(b, pos);
    for (; pos >= 0; pos--) {
        while (Compare(a, b))
            a = a - b;
        ShiftRight(b, 1);
    }
    for (int i = a.len - 1; i >= 0; i--) {
        if (a.val[i] > 0)
            break;
        a.len--;
    }
    return a;
}

BigInteger operator+(BigInteger a, BigInteger b) {
    int temp = 0, carry = 0;
    BigInteger res;
    for (int i = 0; i < a.len || i < b.len; i++) {
        temp = a.val[i] + b.val[i] + carry;
        res.val[res.len++] = temp % 10;
        carry = temp >= 10 ? 1 : 0;
    }
    if (carry)
        res.val[res.len++] = carry;
    return res;
}

BigInteger operator-(BigInteger a, BigInteger b) {
    BigInteger res;
    if (b.flag == -1) return a + b;
    if (Compare(a, b) == 0)
        swap(a, b), res.flag *= -1;

    for (int i = 0; i < a.len || i < b.len; i++) {
        if (a.val[i] < b.val[i]) {
            a.val[i + 1]--, a.val[i] += 10;
        }
        res.val[res.len++] = a.val[i] - b.val[i];
    }
    while (res.len - 1 >= 1 && res.val[res.len - 1] == 0)
        res.len--;
    return res;
}

BigInteger operator*(BigInteger &a, BigInteger &b) {
    BigInteger res;
    res = Karatsuba(a, b);
    res.flag = a.flag * b.flag;
    return res;
}

BigInteger operator/(BigInteger a, BigInteger b) {
    int pos = a.len - b.len, C = Compare(a, b);
    BigInteger res;
    res.flag = a.flag * b.flag;
    if (C == 2) return res = 1;
    if (C == 0) return res = 0;
    ShiftLeft(b, pos);
    res.len = pos + 1;
    for (; pos >= 0; pos--) {
        while (Compare(a, b)) {
            a = a - b;
            res.val[pos]++;
        }
        ShiftRight(b, 1);
    }
    for (int i = res.len - 1; i >= 0; i--, res.len--)
        if (res.val[i]) break;
    return res;
}

BigInteger ModPow(BigInteger a, BigInteger b, BigInteger mod) {
    BigInteger ans(1), base = a % mod;
    while (Compare(b, ZERO) != 2) {
        if (Compare(b % 2, ONE) == 2)
            ans = ans * base % mod;
        base = base * base % mod;
        b = b / 2;
    }
    return ans % mod;
}

BigInteger ModMul(BigInteger a, BigInteger b, BigInteger mod) {
    BigInteger ans(0), base = a % mod;
    while (Compare(b, ZERO) != 2) {
        if (Compare(b % 2, ONE) == 2)
            ans = ans + base % mod;
        base = (base + base) % mod;
        b = b / 2;
    }
    return ans;
}

BigInteger GCD(BigInteger a, BigInteger b) {
    if (Compare(b, ZERO) == 2)
        return a;
    return GCD(b, a % b);
}

void ExGCD(BigInteger a, BigInteger b, BigInteger &x, BigInteger &y) {
    if (Compare(b, ZERO) == 2) {
        x = 1;
        y = 0;
        return;
    }
    ExGCD(b, a % b, y, x);
    BigInteger c = a / b;
    c = c * x;
    y = y - c;
}

BigInteger Inv(BigInteger a, BigInteger b) {
    BigInteger x, y;
    ExGCD(a, b, x, y);
    return (x % b + b) % b;
}

bool MillerRabin(BigInteger p) {
    if (Compare(p, BigInteger(2)) == 0)
        return false;
    if (Compare(p, BigInteger(2)) != 2 && Compare(p % 2, ZERO) == 2)
        return false;
    BigInteger s = p - 1;
    int i;
    while (Compare(s % 2, ZERO) == 2)
        s = s / 2;
    for (i = 0; i < 2; i++) {
        if (Compare(p, prime[i]) == 2)
            return true;
        BigInteger t = s, m = ModPow(prime[i], s, p);
        while (!IsEqual(t, p - 1) && !IsEqual(m, 1) && !IsEqual(m, p - 1)) {
            m = ModMul(m, m, p);
            BigInteger q(2);
            t = t * q;
        }
        if (!IsEqual(m, p - 1) && Compare(t % 2, ZERO) == 2)
            return false;
    }
    return true;
}

string Base64::Encode(unsigned  char *str) {
   // cout<<str<<endl;
    int num = 0, bin = 0, i, bytes = 0;
    std::string _encode_result;
    for (; str[bytes] != '\0'; bytes++);
    unsigned char *current = str;
    //current = str;
    while (bytes > 2) {
        _encode_result += _base64_table[current[0] >> 2];
        _encode_result += _base64_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
        _encode_result += _base64_table[((current[1] & 0x0f) << 2) + (current[2] >> 6)];
        _encode_result += _base64_table[current[2] & 0x3f];

        current += 3;
        bytes -= 3;
    }
    if (bytes > 0) {
        _encode_result += _base64_table[current[0] >> 2];
        if (bytes % 3 == 1) {
            _encode_result += _base64_table[(current[0] & 0x03) << 4];
            _encode_result += "==";
        } else if (bytes % 3 == 2) {
            _encode_result += _base64_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
            _encode_result += _base64_table[(current[1] & 0x0f) << 2];
            _encode_result += "=";
        }
    }
    return _encode_result;
}

string Base64::Decode(char *str) {
    int length = 0;
    for (; str[length] != '\0'; length++);
    const char DecodeTable[] =
            {
                    -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -2, -2, -1, -2, -2,
                    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
                    -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 62, -2, -2, -2, 63,
                    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -2, -2, -2, -2, -2, -2,
                    -2, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -2, -2, -2, -2, -2,
                    -2, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
                    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -2, -2, -2, -2, -2,
                    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
                    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
                    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
                    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
                    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
                    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
                    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
                    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2
            };
    int bin = 0, i = 0, pos = 0;
    std::string _decode_result;
    const char *current = str;
    char ch;
    while ((ch = *current++) != '\0' && length-- > 0) {
        if (ch == base64_pad) {

            if (*current != '=' && (i % 4) == 1) {
                return NULL;
            }
            continue;
        }
        ch = DecodeTable[ch];

        if (ch < 0) {
            continue;
        }
        switch (i % 4) {
            case 0:
                bin = ch << 2;
                break;
            case 1:
                bin |= ch >> 4;
                _decode_result += bin;
                bin = (ch & 0x0f) << 4;
                break;
            case 2:
                bin |= ch >> 2;
                _decode_result += bin;
                bin = (ch & 0x03) << 6;
                break;
            case 3:
                bin |= ch;
                _decode_result += bin;
                break;
        }
        i++;
    }
    return _decode_result;
}