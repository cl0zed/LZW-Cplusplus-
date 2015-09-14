#ifndef __16bit__
#define __16bit__
#include<bitset>
#include <iostream>
#include<fstream>
using namespace std;
typedef unsigned char uchar;
class obitfstream: public ofstream
{
    uchar bitcount;
    uchar buffer;
public:
    obitfstream():bitcount(0),buffer(0){}
    obitfstream(const char *fname): ofstream(fname, std::ios_base::binary),bitcount(0){}
    void putBit(bool x)
    {
		buffer = (buffer<<1) | static_cast<uchar>(x);
        ++bitcount;
        if (bitcount==8) bitcount = 0;
        if (bitcount==0) { put(buffer); buffer = 0;}
    }
    void close()
    {
        if (bitcount>0)
            put(buffer);
        buffer=0;
        bitcount=0;
        ofstream::close();
    }
};

class ibitfstream: public ifstream
{
    uchar buffer;
    uchar bitcount;
public:
    ibitfstream():bitcount(0),buffer(0){}
    ibitfstream(const char *fname): ifstream(fname,std::ios_base::binary),bitcount(0){}
    int getBit()
    {
        if (bitcount==8) bitcount = 0;
        if (bitcount==0) buffer = get();
        int i;
        i = buffer & (1<<(7-bitcount)) ? 1:0;
        ++bitcount;
        return i;
    }
    bool eof()
    {
        if (bitcount<8 && bitcount>0)
            return false;
        // return isftream::eof();
        if (peek()!=EOF)
            return false;
        return true;
    }
};

struct newbit
{
	unsigned short int k;
	newbit set(int i)
	{
		k = i;
		return *this;
	}
	int value()
	{
		return k;
	}
};
std::ostream& operator <<(std::ostream& out, const newbit& a)
{
	out << a.k;
	return out;
}
obitfstream& operator <<(obitfstream& out, const newbit& a)
{
	short int tmp = a.k;
	for (int i = 0; i<12; ++i)
	{
		out.putBit(tmp%2);
		tmp /= 2;
	}
	return out;
}
ibitfstream& operator >>(ibitfstream& in, newbit& a)
{
	bitset<12> h;
	for (int i = 0; i< 12; ++i)
		h[i] = in.getBit();
	a.k = h.to_ulong();
	return in;
}

#endif