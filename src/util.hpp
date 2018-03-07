#include<openssl/sha.h>
#include<iostream>
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
