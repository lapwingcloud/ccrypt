# ccrypt

C++的AES-128和Base64库，AES目前只实现了ECB和PKCS7 padding
为了速度考虑，AES依赖于openmp，暂时没有不依赖的版本。
如果需要去掉依赖，去掉源码AES.cpp中的两个`#pragma`然后修改makefile即可

# 编译

```
make
```
会在当前文件夹下生成`libccrypt.a`

# 使用示例

```
#include <string>
#include "ccrypt.h"
using namespace std;
using namespace ccrypt;

byte key[] = {
    0xBC, 0x44, 0x23, 0x30,
    0xAE, 0xDE, 0x09, 0x79,
    0x55, 0x83, 0x70, 0xA1,
    0x66, 0x21, 0x07, 0x9B
};
AES aes(key);

int main()
{
    string enc = aes.encrypt("wangdai");
    string dec = aes.decrypt(enc);
    return 0;
}
```

```
g++ -Ipath/to/ccrypt/include -Lpath/to/ccrypt -o yourprogram yourprogram.cpp -lccrypt -lgomp
```

# 测试

```
make test
./test
```

输出大概是这样

<pre>
original string:

alsdjalskdj你alskd好jalksdj呀alksjdlak吧啦吧啦sjdqwejbqwqeqweqweqwescvfv]'f[pb]bl]-30=13-rodsk asdfj qw3    wkjeb12348214

encrypted string (with base64):

UbKxG/9K6rvzWHW1/AQsl+bNEmOi5jZp+iFqD0s1+n8lGa4CIsikR+9fYb2Zq36c0dFsZpzwWYL9
DqS1vGYCQege4AuuAosMHlv75YaI+h6Vpkrc0xXbyIrykl95j0AeV6iprVhAFcpm+N02At1WdS//
tpVeZNQL7LASE5G9P6I04Saatzkck7joYucP9OBH

decrypted string:

alsdjalskdj你alskd好jalksdj呀alksjdlak吧啦吧啦sjdqwejbqwqeqweqweqwescvfv]'f[pb]bl]-30=13-rodsk asdfj qw3    wkjeb12348214

Test passed
</pre>

# API

## AES

```
/* 初始化一个密钥为key的AES对象，key一定要是16bytes的 */
AES(const byte* key);
/* 对bytes进行AES-128加密及PKCS7 padding */
vector<byte> encrypt(const byte* bytes, int len);
/* 跟上面函数一样 */
vector<byte> encrypt(const vector<byte>& bytes);
/* 先把text视为bytestring，加密后再用Base64编码 */
string encrypt(const string& text);
/* 对bytes进行AES-128解密及去除PKCS7 padding，len一定要是16的倍数 */
vector<byte> decrypt(const byte* bytes, int len);
/* 跟上面函数一样 */
vector<byte> decrypt(const vector<byte>& bytes);
/* 先用Base64解码，然后跟上面一样 */
string decrypt(const string& text);
```

## Base64

```
static string encode(const vector<byte> &bytes);
static vector<byte> decode(const string &str);
```
