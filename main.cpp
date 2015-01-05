#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include "AES.h"

using namespace std;

void test();

int main()
{
    // test();
    cout << AES::encrypt("alsdjalskdjalskdjalksdjalksjdlaksjdqwejbqwqeqweqweqwescvfv]'f[pb]bl]-30=13-rodsk asdfj qw3    wkjeb12348214 \n\t");
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

void test()
{
    ifstream fin("testin.txt");
    ofstream foutenc("testoutenc.txt"), foutdec("testoutdec.txt");
    string sin = read_file_str(fin);
    string enc = AES::encrypt(sin);
    foutenc << enc;
    foutdec << AES::decrypt(enc);
}
