#include "BASE.h"
#include "MD5.h"
#include "AffineCipher.h"
int main() {
//   string a,b;
//   for(int i = 1;i<=1020;i++) a+=1,b+=2;
//   BigInteger A(a),B(b);
//   A= A*B;
//   cout<<A.len;
//BigInteger a("3"),b("11");
// a = Inv(a,b);
//BigInteger a(4),b(2);
//a = a/b;
//cout<<a;
//    BigInteger a(28),b(8),c(100);
//    c = ModMul(a,b,c);
//cout<<c<<endl;
    BigInteger a(
            "10948300812331076071251281934958703326040310436403504167280585592426040276363497949160832605686225126658064611288334171095069240223419414396925146605701823");
    cout << MillerRabin(a);
//    MD5 x;
//    string a = "";
//    cout << x.GenerateMd5(a) << endl;
//计算机学院网络工程信息安全，我们热爱中华人民共和国。大家
//和院程安我爱计
//string a;
//string b;
//cin>>a>>b;
//AffineCipher x(a,b);
//x.Decode();


}

