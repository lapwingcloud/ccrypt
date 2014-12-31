#ifndef XORINTEGER_H
#define XORINTEGER_H


class XorInteger {
public:
    // public static variables
    static const int width = 8*sizeof(unsigned);
    static const int irreducible = 0x11B;
    // constructors and destructors
    XorInteger();
    XorInteger(unsigned val);
    virtual ~XorInteger();
    // normal public methods
    XorInteger inv();
    // getter and setter
    unsigned val();
    void set_val(unsigned val);
    // operator overload
    void operator=(unsigned a);
    void operator=(XorInteger a);
    friend XorInteger operator+(XorInteger a, XorInteger b);
    friend XorInteger operator-(XorInteger a, XorInteger b);
    friend XorInteger operator*(XorInteger a, XorInteger b);
    friend XorInteger operator/(XorInteger a, XorInteger b);
    friend XorInteger operator%(XorInteger a, XorInteger b);
    // static methods
    static XorInteger inv(XorInteger a);
    static XorInteger egcd(XorInteger a, XorInteger b);
    static XorInteger egcd(XorInteger a, XorInteger b, XorInteger &x, XorInteger &y);
protected:
private:
    unsigned val_;
};

void egcd(unsigned a, unsigned b);
std::pair<unsigned, unsigned> divmod(unsigned a, unsigned b);

#endif // XORINTEGER_H
