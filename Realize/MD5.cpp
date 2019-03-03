//
// Created by DeepWave on 2019/2/27.
//

#include "../Header/MD5.h"

MD5::MD5() {
    ua = KA;
    ub = KB;
    uc = KC;
    ud = KD;
}

string ToHex(unsigned int n) {
    string res = "";
    unsigned char *temp = (unsigned char *) &n;
    for (int i = 0; i < 4; i++) {
        unsigned char num;
        num = temp[i] & 0xf0;
        num = num >> 4;
        res += h[num];
        num = temp[i] & 0x0f;
        res += h[num];
    }
    return res;
}

UI ShiftLeft(UI src, int n) {
    return ((src << n) | (src >> (32 - n)));
}

int FillData(string s, unsigned char **output) {
    string res;
    unsigned char *src = (unsigned char *) s.c_str();
    int total_len = s.length() * BYTE_LEN;
    int block_num = total_len / BLOCK_LEN;
    int rem_num = total_len % BLOCK_LEN;
    int fill_num = 0;
    if (rem_num >= BLOCK_FILL_MAX)
        fill_num = BLOCK_FILL_MAX + BLOCK_LEN - rem_num;
    else
        fill_num = BLOCK_FILL_MAX - rem_num;
    total_len += fill_num;
    *output = new unsigned char[(total_len + 64) / BYTE_LEN];
    memset(*output, 0, (size_t) (total_len + 64) / BYTE_LEN);
    memcpy(*output, src, s.length());
    unsigned char *temp = *output;
    temp += s.length();
    *temp = 0x80;
    unsigned long long *src_len = (unsigned long long *) ((*output) + ((total_len / BYTE_LEN)));
    *src_len = s.length() * BYTE_LEN;
    return (total_len + 64) / BYTE_LEN;
}

void MD5::TurnOperation(unsigned char *src) {
    if (src == NULL)
        return;
    int pos[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7,
                   12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
                   4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10,
                   15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
    unsigned int *temp = reinterpret_cast<unsigned int *>(src);
    unsigned int a = ua, b = ub, c = uc, d = ud;
    for (int i = 0; i < 64; i++) {
        unsigned int y = B_MD5 * abs(sin(i + 1));
        unsigned int x ,t;
        int j;
        switch (i / 16) {
            case 0:
                x = F(b, c, d);
                j = i;
                break;
            case 1:
                x = G(b,c,d);
                j = (i*5+1)%16;
                break;
            case 2:
                x = H(b,c,d);
                j = (i*3+5)%16;
                break;
            case 3:
                x = I(b,c,d);
                j = (i*7)%16;
                break;
        }
        t = d;
        d = c;
        c = b;
        b=b+ShiftLeft((a+x+y+temp[j]),pos[i]);
        a = t;
    }
    ua = a + KA;
    ub = b + KB;
    uc = c + KC;
    ud = d + KD;
}

string MD5::GenerateMd5(string s) {
    string res = "";
    unsigned char *data = NULL;
    int data_len = FillData(s, &data);
    unsigned char *Block = data;
    for (int i = 0; i < data_len / (BLOCK_LEN / BYTE_LEN); i++) {
        Block += i * (BLOCK_LEN / BYTE_LEN);
        TurnOperation(Block);
    }
    res += ToHex(ua);
    res += ToHex(ub);
    res += ToHex(uc);
    res += ToHex(ud);
    return res;
}
