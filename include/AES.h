#ifndef AES_H
#define AES_H

#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include "Base64.h"

typedef unsigned char byte;

byte mul(byte a, byte b);

class AES {
public:
    static const int block_size = 16; // bytes

    AES();
    virtual ~AES();
    static std::string encrypt(const std::string &text);
    static void encrypt(byte *text);
    static std::string decrypt(const std::string &text);
    static void decrypt(byte *text);
    static int init_ekey();

private:
    static const byte sbox[256];
    static const byte sbox_inv[256];
    static const byte coef[4];
    static const byte coef_inv[4];
    static const byte rc[11];
    static byte key[block_size];
    static byte ekey[11 * block_size];
    static int trick;

    static void add_round_key(byte *block, byte *key);
    static void transpose(byte *block);
    static void sub_bytes(byte *block, bool decrypt);
    static void shift_rows(byte *block, bool decrypt);
    static void mix_columns(byte *block, bool decrypt);
    static void expansion(byte *key, byte *ekey);
};

#endif // AES_H
