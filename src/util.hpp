#pragma once
#include<openssl/sha.h>
#include<iostream>
#include<vector>
#include<iomanip>
#include<sstream>
#include<string.h>

namespace crypto{
	void sha256(std::string & input, std::string md);
	std::string sha256(std::string && input, std::string md);
	template<typename ... Inputs>
		void sha256hashing(std::string & first, Inputs& ... other, std::string md){
			sha256( first, md );
			sha256hashing(other..., md);
		}
}

namespace Text{
		std::vector<std::string> split(std::string, const char);
		void deleteChar(char * t, const char ch='\n', const char cht=0);
		bool correct_name(const char * buf);
}
