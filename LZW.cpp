
#include "stdafx.h"
#include "LZWcompression.h"
#include<iostream>
#include <fstream>
#include<string>
#include<ctime>
#include"16bit.h"

int main(int argc, _TCHAR* argv[])
{
		LZWencode toEncode;
		LZWDecode toDecode;
		char c[1024] , d[1024];
		std::cout << "Please insert name of input file:" << std::endl;
		std::cin.getline(c, 1024);
		std::cout << "Please insert name of output file:" << std::endl;
		std::cin.getline(d, 1024);
		int tic = time(NULL);
		try
		{
			toEncode(c, "encode.txt");
			std::cout << "Name of compression file: encode.txt" << std::endl;
			toDecode("encode.txt",d);
		}catch (char*E) {std::cout << E <<endl;}
		std::cout <<"Time for encode: " << time(NULL) - tic << endl;
		system("pause");
		return 0;
}

		