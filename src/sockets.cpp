#include"sockets.hpp"

namespace Sockets{
	int socket(int domain, int type, int protocol){
		return socket(domain, type, protocol);
	}

	int connect(int fd, const char * addr, unsigned int port, short unsigned int domain){
		struct hostent * host = gethostbyname(addr);
		if(host == NULL) throw( std::runtime_error("Cannot found host") );
		
		struct sockaddr_in adr = { domain, htons(port) };
		memcpy(&adr.sin_addr, host->h_addr_list[0], host->h_length);
		int tmp = connect(fd,(struct sockaddr*)&adr,sizeof(adr));
		if(tmp <= 0) throw ( std::runtime_error("Cannot connect to host" + std::string(addr) ) );
		return tmp;
	}

	int bind(int fd, const char * addr, unsigned int port, short unsigned int domain){
			struct sockaddr_in adr = { domain, htons(port) };
			adr.sin_addr.s_addr = inet_addr(addr);
			int tmp = bind(fd, (const sockaddr*)&adr, sizeof(adr));
			if(tmp <= 0) 
				throw ( 
					std::runtime_error( "Cannot bind " + std::string(addr)  )
 				);
			return tmp;			
	}

	std::string read_sock(int fd, int max_size=maxsize){
		char buf[sizebuf];
		std::string ret;
		int n;
		do{
			n = read(fd, buf, sizebuf);
			if(buf[0] == 0) throw( std::runtime_error("closed connection") );
			ret.append(buf);
			bzero(buf, sizebuf);
		}while( n == sizebuf && ret.size() < max_size );
		return ret;
	}

	void write_sock(int fd, std::string msg){
		if ( write(fd, msg.c_str(), msg.size()) <= 0)
			throw( std::runtime_error("Cannot write") );
	}
}
