#include"util.hpp"
namespace crypto{
		std::string sha256(std::string && input, std::string md){
			std::string returns = input;
			sha256(returns, md);
			return returns;
		}
		void sha256(std::string & input, std::string md){
			unsigned char md_[SHA256_DIGEST_LENGTH];
			memcpy(md_, md.c_str(), SHA256_DIGEST_LENGTH);
			SHA256_CTX context;
			if(!SHA256_Init(&context)) 
				throw( std::runtime_error("sha256_openssl init error") );
			if(!SHA256_Update(&context, (unsigned char*)input.c_str(), input.size() )) 
				throw( std::runtime_error("sha256_openssl update error"));
			 if(!SHA256_Final(md_, &context))
        			throw( std::runtime_error("sha256_openssl final error"));

                                    std::ostringstream ret;
                                    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i)
                                                ret << std::hex << std::setfill('0') << std::setw(2) << std::uppercase << int(md_[i]);
                                    
                                    input = ret.str();
		}
}

namespace Text{
                        void deleteChar(char * t, const char ch, const char cht){
                                    while(*t){
                                           if(*t == ch)
                                                *t=cht;
                                           *(t++);
                                    }
                        }


                        std::vector<std::string> split(std::string text, const char dim){
                                    deleteChar((char *)text.c_str());
                                    std::vector<std::string> strings;
                                    std::istringstream msg(text);
                                    std::string tmp;
                                    while (getline(msg, tmp, dim)) {
                                    	strings.push_back(tmp);
                                    }
                                    return std::move(strings);
                        }
                        
                        bool correct_name(const char * buf){
                                    while( *buf ){
                                                if( !(*buf >= 'a' && *buf <= 'z') &&
				   !(*buf >='1' && *buf <= '9') &&
					!(*buf >= 'A' && *buf <= 'Z' ) )
					return false;
                                                (buf++);
			}
			return true;            
                        }
}
