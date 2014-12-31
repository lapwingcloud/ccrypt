#ifndef BASE64_H
#define BASE64_H

#include <string>
#include <vector>

typedef unsigned char byte;

class Base64 {
public:
    Base64();
    virtual ~Base64();
    static std::string encode(const std::vector<byte> &bytes);
    static std::vector<byte> decode(const std::string &str);
    static int init_rtable();
private:
    static int trick;
    static const char *table;
    static byte rtable[128];
};

#endif // BASE64_H
