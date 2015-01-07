#include "Base64.h"

const char *Base64::table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
byte Base64::rtable[128];
int trick = Base64::init_rtable();

Base64::Base64()
{
    //ctor
}

Base64::~Base64()
{
    //dtor
}

std::string Base64::encode(const std::vector<byte> &bytes)
{
    int i, j, len = bytes.size();
    std::string str;
    for (i=0; i < len; i+=3) {
        byte b0 = bytes[i];
        byte b1 = (i+1 < len) ? bytes[i+1] : 0;
        byte b2 = (i+2 < len) ? bytes[i+2] : 0;
        str.push_back(table[b0>>2]);
        str.push_back(table[((b0&0x3)<<4)|(b1>>4)]);
        str.push_back(table[((b1&0xf)<<2)|(b2>>6)]);
        str.push_back(table[b2&0x3f]);
    }
    if (len % 3 == 1) {
        str[str.length()-2] = '=';
        str[str.length()-1] = '=';
    } else if (len % 3 == 2) {
        str[str.length()-1] = '=';
    }
    int slen = str.length();
    for (i=line_width, j=0; i < slen; i+=line_width, j++) {
        str.insert(i+j, "\n");
    }
    return str;
}

std::vector<byte> Base64::decode(const std::string &str)
{
    int i = 0, len = str.length();
    std::vector<byte> result;
    for (i = 0; i < len; i += 4) {
        byte c0 = rtable[(byte) str[i]];
        byte c1 = rtable[(byte) str[i+1]];
        byte c2 = rtable[(byte) str[i+2]];
        byte c3 = rtable[(byte) str[i+3]];
        byte b0 = (c0<<2)|((c1>>4)&0x3);
        byte b1 = (c1<<4)|((c2>>2)&0xf);
        byte b2 = (c2<<6)|(c3&0x3f);
        result.push_back(b0);
        result.push_back(b1);
        result.push_back(b2);
        if (i+4 < len && str[i+4] == '\n') {
            i++;
        }
    }
    int count = 0;
    for (int i = len-1; i >= 0; i--) {
        if (str[i] == '\n') {
            continue;
        } else if (str[i] == '=') {
            count++;
        } else {
            break;
        }
    }
    if (count > 0) {
        result.pop_back();
        if (count > 1) {
            result.pop_back();
        }
    }
    return result;
}

int Base64::init_rtable()
{
    for (int i = 'A'; i <= 'Z'; i++) {
        rtable[i] = i-'A';
    }
    for (int i = 'a'; i <= 'z'; i++) {
        rtable[i] = i-'a'+26;
    }
    for (int i = '0'; i <= '9'; i++) {
        rtable[i] = i-'0'+52;
    }
    rtable['+'] = 62;
    rtable['/'] = 63;
    return 0;
}
