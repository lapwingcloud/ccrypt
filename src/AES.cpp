#include "AES.h"

using namespace ccrypt;

const byte AES::SBOX[256] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

const byte AES::SBOX_INV[256] = {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};

const byte AES::COEF[4] = {0x02, 0x03, 0x01, 0x01};
const byte AES::COEF_INV[4] = {0x0E, 0x0B, 0x0D, 0x09};
const byte AES::RC[ROUNDS] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};


AES::AES(const byte* key)
{
    // AES::ekey = expansion(key);
    expansion(key, ekey);
    for (int i = 0; i < ROUNDS; i++) {
        transpose(ekey + i*BLOCK_SIZE);
    }
}

std::string AES::encrypt(const std::string& text)
{
	return Base64::encode(encrypt((const byte*) text.data(), text.size()));
}

std::vector<byte> AES::encrypt(const std::vector<byte>& bytes)
{
    return encrypt(bytes.data(), bytes.size());
}

std::vector<byte> AES::encrypt(const byte* bytes, int len)
{
    // expand input bytes to n*BLOCK_SIZE
    int diff = BLOCK_SIZE - len%BLOCK_SIZE;
    int explen = len + diff;
    byte expbytes[explen];
    memcpy(expbytes, bytes, len);
    // PKCS7 padding
    memset(expbytes+len, diff, diff);
    // encrypt each block in order
    #pragma omp parallel for
    for (int i = 0; i < explen; i += BLOCK_SIZE) {
        encrypt_block(expbytes + i);
    }
    return std::vector<byte>(expbytes, expbytes+explen);
}

std::string AES::decrypt(const std::string& text)
{
    std::vector<byte> strbytes = decrypt(Base64::decode(text));
    return std::string(strbytes.begin(), strbytes.end());
}

std::vector<byte> AES::decrypt(const std::vector<byte>& bytes)
{
    return decrypt(bytes.data(), bytes.size());
}

std::vector<byte> AES::decrypt(const byte* bytes, int len)
{
    int safelen = len;
    while (safelen % BLOCK_SIZE) safelen++;
    byte cpbytes[safelen];
    memcpy(cpbytes, bytes, len);
    // decrypt each block in order
    #pragma omp parallel for
    for (int i = 0; i < safelen; i += BLOCK_SIZE) {
        decrypt_block(cpbytes + i);
    }
    // remove PKCS7 padding
    int diff = (cpbytes[len-1] <= BLOCK_SIZE) ? cpbytes[len-1] : 0;
    return std::vector<byte>(cpbytes, cpbytes+len-diff);
}

void AES::encrypt_block(byte* text)
{
    transpose(text);
    add_round_key(text, ekey);
    for (int i = 1; i < ROUNDS; i++) {
        sub_bytes(text, ENCRYPTION);
        shift_rows(text, ENCRYPTION);
        if (i < (ROUNDS-1)) {
            mix_columns(text, ENCRYPTION);
        }
        add_round_key(text, ekey + i*BLOCK_SIZE);
    }
    transpose(text);
}

void AES::decrypt_block(byte* text)
{
    transpose(text);
    add_round_key(text, ekey + (ROUNDS-1)*BLOCK_SIZE);
    for (int i = ROUNDS-2; i >= 0; i--) {
        shift_rows(text, DECRYPTION);
        sub_bytes(text, DECRYPTION);
        add_round_key(text, ekey + i*BLOCK_SIZE);
        if (i > 0) {
            mix_columns(text, DECRYPTION);
        }
    }
    transpose(text);
}

void AES::add_round_key(byte *block, const byte* key)
{
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i];
    }
}

void AES::sub_bytes(byte *block, int direction)
{
    const byte *mat = (direction == ENCRYPTION) ? SBOX : SBOX_INV;
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] = mat[block[i]];
    }
}

void AES::shift_rows(byte *block, int direction)
{
    if (direction == ENCRYPTION) {
        for (int i = 0; i < 3; i++) {
            std::swap(block[4+i], block[5+i]);
            std::swap(block[15-i], block[14-i]);
        }
    } else {
        for (int i = 0; i < 3; i++) {
            std::swap(block[7-i], block[6-i]);
            std::swap(block[12+i], block[13+i]);
        }
    }
    std::swap(block[8], block[10]);
    std::swap(block[9], block[11]);
}

void AES::mix_columns(byte *block, int direction)
{
    byte tmp[BLOCK_SIZE];
    const byte* coef = (direction == ENCRYPTION) ? COEF : COEF_INV;
    for (int i = 0; i < BLOCK_SIZE; i++) {
        tmp[i] = block[i];
    }
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] = 0;
        for (int j = 0; j < 4; j++) {
            block[i] ^= mul(coef[j], tmp[(i+4*j) % 16]);
        }
    }
}

void AES::expansion(const byte* key, byte *ekey)
{
    // copy the first block
    for (int i = 0; i < BLOCK_SIZE; i++) {
        ekey[i] = key[i];
    }
    // expand 1 block to 11 blocks
    byte gword[4];
    for (int i = 1; i < 11; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            int curr_word = i*BLOCK_SIZE + j;
            int last_word = curr_word - 4;
            int last_block = curr_word - BLOCK_SIZE;
            if (j == 0) {
                for (int k = 0; k < 4; k++) {
                    gword[k] = ekey[curr_word - 4 + k];
                }
                // one-byte left circular rotation
                for (int k = 0; k < 3; k++) {
                    std::swap(gword[k], gword[k+1]);
                }
                for (int k = 0; k < 4; k++) {
                    gword[k] = SBOX[gword[k]];
                }
                gword[0] ^= RC[i];
            }
            if (j < 4) {
                ekey[curr_word] = ekey[last_block] ^ gword[j];
            } else {
                ekey[curr_word] = ekey[last_word] ^ ekey[last_block];
            }
        }
    }
}

void ccrypt::transpose(byte *block)
{
    for (int i = 0; i < 4; i++) {
        for (int j = i+1; j < 4; j++) {
            std::swap(block[4*i + j], block[4*j + i]);
        }
    }
}

byte ccrypt::mul(byte a, byte b)
{
    unsigned short result = 0;
    for (int i = 0; i < 8; i++) {
        if (b & (1<<i)) {
            result ^= (a<<i);
        }
    }
    if (result > 0xff) {
        for (int i = 15; i >= 8; i--) {
            if (result & (1<<i)) {
                result ^= (0x11B<<(i-8));
            }
        }
    }
    return result;
}
