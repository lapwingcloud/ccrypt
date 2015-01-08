#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include "ccrypt.h"

using namespace std;
using namespace ccrypt;

bool test();
bool test2();

byte key[] = {
    0xBC, 0x44, 0x23, 0x30,
    0xAE, 0xDE, 0x09, 0x79,
    0x55, 0x83, 0x70, 0xA1,
    0x66, 0x21, 0x07, 0x9B
};
AES aes(key);

int main()
{
    //test();
    if (test2()) {
        cout << "Test passed" << endl;
    } else {
        cout << "Test Failed" << endl;
    }
    return 0;
}

string read_file_str(ifstream &fin)
{
    string result, tt;
    while (getline(fin, tt)) {
        result.append(tt + '\n');
    }
    result.erase(result.end()-1);
    return result;
}

bool test()
{
    ifstream fin("testin.txt");
    ofstream foutenc("testoutenc.txt"), foutdec("testoutdec.txt");
    string sin = read_file_str(fin);
    string enc = aes.encrypt(sin);
    string dec = aes.decrypt(enc);
    foutenc << enc;
    foutdec << dec;
    return sin == dec;
}

bool test2()
{
    string s = "alsdjalskdj你alskd好jalksdj呀alksjdlak吧啦吧啦sjdqwejbqwqeqweqweqwescvfv]'f[pb]bl]-30=13-rodsk asdfj qw3    wkjeb12348214";
    cout << "original string:" << endl << endl << s << endl << endl;
    string enc = aes.encrypt(s);
    cout << "encrypted string (with base64):" << endl << endl << enc << endl << endl;
    string dec = aes.decrypt(enc);
    cout << "decrypted string:" << endl << endl << dec << endl << endl;
    return s == dec;
}

