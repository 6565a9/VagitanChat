#include<openssl/sha.h>
#include<iostream>
#include<string.h>

namespace crypto{
	void sha256(std::string & input, std::string md);
	std::string sha256(std::string && input, std::string md);
	
}
