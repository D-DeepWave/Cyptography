//
// Created by DeepWave on 2019/2/25.
//

#include"BASE.h"

int prime[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
string a = "10635010491070485936958241536719958460977717954627695365192387766441672796909369543973733914490304731489421410349648857630148526654763195250530496217393819";
string b = "10948300812331076071251281934958703326040310436403504167280585592426040276363497949160832605686225126658064611288334171095069240223419414396925146605701823";
BigInteger P[2] = {a, b};

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

int Compare( BigInteger a, BigInteger b) {
    if (a.flag != b.flag)
        return a.flag > b.flag;
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
    for(int i = a.len-1;i>=0&&a.val[i];i--,a.len--);
    for(int i = b.len-1;i>=0&&b.val[i];i--,b.len--);
    if (a.len != b.len) return false;
    for (int i = 0; i < a.len; i++) {
        if (a.val[i] != b.val[i])
            return false;
    }
    return true;
}

BigInteger ShiftLeft(BigInteger &a, int b) {
    if (a.len == 0) return 0;
    for (int i = a.len - 1; i >= 0; i--) {
        int x = i + b;
        a.val[x] = a.val[i];
    }
    for (int i = b - 1; i >= 0; i--)
        a.val[i] = 0;
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
    BigInteger z0 = Karatsuba(x1, y1);
    BigInteger z1 = Karatsuba(x1 + x2, y1 + y2);
    BigInteger z2 = Karatsuba(x2, y2);
    BigInteger r1 = z2, r2 = z1 - z2 - z0;
    ShiftLeft(r1, 2 * (len - mid));
    ShiftLeft(r2, len - mid);
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
    for (int i = res.len - 1; i >= 0; i--) {
        if (res.val[i] > 0)
            break;
        res.len--;
    }
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
    int  i;
    while (Compare(s % 2, ZERO) == 2)
        s = s / 2;
    for (i = 0; i < 10 ; i++) {
        if(Compare(p,prime[i])==2)
            return true;
        BigInteger t = s,m = ModPow(prime[i],s,p);
        while(!IsEqual(t,p-1)&&!IsEqual(m,1)&&!IsEqual(m,p-1))
        {
            m = ModMul(m,m,p);
            BigInteger q (2);
            t = t * q;
        }
        if(!IsEqual(m,p-1)&&Compare(t%2,ZERO)==2)
            return false;
    }
    return true;
}