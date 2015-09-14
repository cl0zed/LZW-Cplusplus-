#ifndef ___LZW___
#define ___LZW___
#include<hash_map>
#include<string>
#include<fstream>
#include"16bit.h"


;using namespace std;
class LZWencode
{
	hash_map<string, int> m;
	string buffer;
	char x;
	int j;
public:
	LZWencode():j(255)
	{
		for (unsigned short i = 0; i < 256; ++i)
		{
			m[buffer + (char)i] = i;
		}
	}
	void operator()(const char* str,const char* outstr)
	{
		newbit h;
		int size = 4096;
		ibitfstream in(str);
		if (!in) throw "can't open input file";
		obitfstream out(outstr);
		while (in.peek() != EOF)
		{
			in.get(x);
			if (m.find(buffer + x) != m.end())
				buffer += x;
			else
			{	
				out << h.set(m[buffer]);
				buffer += x;
				if (j < size - 1)
					m[buffer] = ++j;
				buffer = x;
			}
		}
		out << h.set(m[buffer]);
		in.close();
		out.close();
	}
};
class LZWDecode
{
	hash_map<int, string> m2;
	int j;
public:
	LZWDecode():j(255)
	{
		string buffer;
		for (short i = 0; i < 256; ++i)
		{
			m2[i] = buffer+(char)i;
		}
	}
	void operator()(const char* instr, const char* outstr)
	{
		int size = 4096;
		newbit old_code, new_code;

		string buffer;
		char symbol;
		ibitfstream in(instr);
		obitfstream out(outstr);
		in >> old_code;
		out << m2[old_code.value()];
		symbol = m2[old_code.value()][0];
		while (in >> new_code)
		{
			if (m2.find(new_code.value()) == m2.end())
			{
				buffer = m2[old_code.value()];
				buffer += symbol;
			}else
				buffer = m2[new_code.value()];
			out << buffer;
			symbol = buffer[0];
			if (j < size - 1) m2[++j] = m2[old_code.value()]+symbol;
			old_code = new_code;
		}
		in.close();
		out.close();
	}
};

#endif