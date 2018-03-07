#include <openssl/sha.h>
#include<string>

namespace crypto{
	void sha256(std::string & input, std::string md)
	{
		unsigned char md_[SHA256_DIGEST_LENGTH];
		memcpy(md_, md.c_str(), SHA256_DIGEST_LENGTH);
    		SHA256_CTX context;
    		if(!SHA256_Init(&context)) 
			throw( std::runtime_error("sha256_openssl init error") );
    		if(!SHA256_Update(&context, (unsigned char*)input.c_str(), input.size() )) 
			throw( std::runtime_error("sha256_openssl update error"));
   		 if(!SHA256_Final(md_, &context))
        			throw( std::runtime_error("sha256_openssl final error"));
	}
	std::string sha256(std::string && input, std::string md)
	{
		std::string returns = input;
		sha256(returns, md);
		return returns;
	}	
}
