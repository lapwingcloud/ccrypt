#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include "AES.h"

using namespace std;

void test();
void test2();

byte key[] = {
    0x6E, 0xFA, 0x23, 0x30,
    0x3B, 0xDE, 0x90, 0x79,
    0x55, 0x80, 0xD0, 0xA1,
    0x5D, 0x01, 0xD0, 0x9A
};
AES aes(key);

int main()
{
    //test();
    //test2();
    aes.decrypt(key, 16);
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
/*
void test()
{
    ifstream fin("testin.txt");
    ofstream foutenc("testoutenc.txt"), foutdec("testoutdec.txt");
    string sin = read_file_str(fin);
    string enc = AES::encrypt(sin);
    string dec = AES::decrypt(enc);
    if (sin == dec) {
        cout << "true";
    } else {
        cout << "false";
    }
    cout << endl;
    foutenc << enc;
    foutdec << dec;
}

void test2()
{
    string s = "alsdjalskdjalskdjalksdjalksjdlaksjdqwejbqwqeqweqweqwescvfv]'f[pb]bl]-30=13-rodsk asdfj qw3    wkjeb12348214 \n\t";
    if (s == AES::decrypt(AES::encrypt(s))) {
        cout << "true";
    } else {
        cout << "false";
    }
    cout << endl;
}
*/
