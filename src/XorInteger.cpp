#include <iostream>
#include "XorInteger.h"

// constructors and destructors
XorInteger::XorInteger()
{

}

XorInteger::XorInteger(unsigned val)
{
    this->val_ = val;
}

XorInteger::~XorInteger()
{
    //dtor
}


// normal public methods
XorInteger XorInteger::inv()
{
    XorInteger x, y;
    egcd(irreducible, *this, x, y);
    return y;
}


// getter and setter
unsigned XorInteger::val()
{
    return this->val_;
}

void XorInteger::set_val(unsigned val)
{
    this->val_ = val;
}


// operator overloads
void XorInteger::operator=(unsigned a)
{
    this->val_ = a;
}

void XorInteger::operator=(XorInteger a)
{
    this->val_ = a.val_;
}

XorInteger operator+(XorInteger a, XorInteger b)
{
    return XorInteger(a.val_ ^ b.val_);
}

XorInteger operator-(XorInteger a, XorInteger b)
{
    return XorInteger(a.val_ ^ b.val_);
}

XorInteger operator*(XorInteger a, XorInteger b)
{
    unsigned aval = a.val_;
    unsigned bval = b.val_;
    unsigned result = 0;
    for (int i = 0; i < XorInteger::width; i++) {
        if (bval & (1<<i)) {
            result ^= (aval<<i);
        }
    }
    return XorInteger(result);
}

std::pair<unsigned, unsigned> divmod(unsigned a, unsigned b)
{
    std::pair<unsigned, unsigned> result(0, 0);
    if (a == 0) {
        return result;
    }
    int posb;
    for (int i = XorInteger::width-1; i >= 0; i--) {
        if (b & (1<<i)) {
            posb = i;
            break;
        }
    }
    unsigned quo = 0;
    for (int i = XorInteger::width-1; i >= posb; i--) {
        if (a & (1<<i)) {
            a ^= (b<<(i-posb));
            quo |= (1<<(i-posb));
        }
    }
    result.first = quo;
    result.second = a; // remainder;
    return result;
}

XorInteger operator/(XorInteger a, XorInteger b)
{
    return XorInteger(divmod(a.val_, b.val_).first);
}

XorInteger operator%(XorInteger a, XorInteger b)
{
    return XorInteger(divmod(a.val_, b.val_).second);
}


// static methods
XorInteger XorInteger::inv(XorInteger a)
{
    XorInteger x, y;
    egcd(irreducible, a, x, y);
    return y;
}

XorInteger XorInteger::egcd(XorInteger a, XorInteger b)
{
    XorInteger x, y;
    return egcd(a, b, x, y);
}

XorInteger XorInteger::egcd(
    XorInteger a, XorInteger b, XorInteger &x, XorInteger &y)
{
    XorInteger quo, rem;
    XorInteger ps = 1, s = 0;
    XorInteger pt = 0, t = 1;
    XorInteger tmp;
    while (b.val() > 0) {
        quo = a / b;
        rem = a % b;
        // a, b = b, a%b
        a = b;
        b = rem;
        // ps, s = s, ps-quo*s
        tmp = s;
        s = ps - quo * s;
        ps = tmp;
        // pt, t = t, pt-quo*t
        tmp = t;
        t = pt - quo * t;
        pt = tmp;
    }
    x = ps;
    y = pt;
    return a;
}


// just for testing
void egcd(unsigned a, unsigned b)
{
    unsigned quo, rem;
    unsigned ps = 1, s = 0;
    unsigned pt = 0, t = 1;
    unsigned tmp;
    while (b > 0) {
        quo = a / b;
        rem = a % b;
        a = b;
        b = rem;
        tmp = s;
        s = ps - quo * s;
        ps = tmp;
        tmp = t;
        t = pt - quo * t;
        pt = tmp;
    }
    printf("%u %x %x\n", a, ps, pt);
}
