#include"sockets.hpp"

namespace Sockets{
	int socket_create(int domain, int type, int protocol){
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
			if(tmp < 0) 
				throw ( 
					std::runtime_error( "Cannot bind " + std::string(addr)  )
 				);
			return tmp;			
	}

	std::string read_sock(int fd, int max_size){
		char buf[sizebuf];
		std::string ret;
		int n;
		do{
			bzero(buf, sizebuf);
			n = read(fd, buf, sizebuf);
			if(buf[0] == 0 || !n) throw( std::runtime_error("closed connection") );
			ret.append(buf);

		}while( n == sizebuf && ret.size() < max_size );
		return ret;
	}

	void write_sock(int fd, std::string msg){
		if ( write(fd, msg.c_str(), msg.size()) <= 0)
			throw( std::runtime_error("Cannot write") );
	}

	void set_timeout(int & fd, unsigned int sec, unsigned int ms){
    		struct timeval timeout = {sec,ms};

    		if (setsockopt (fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) == -1)
			throw(std::runtime_error("Can't set setsockopt"));

    		if (setsockopt (fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) == -1)
			throw(std::runtime_error("Can't set setsockopt"));		
	}

}
