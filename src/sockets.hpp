#pragma once
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include<unistd.h>

#include<string.h>


#include<iostream>



namespace Sockets{
	constexpr unsigned int sizebuf = 1024;
	constexpr unsigned int maxsize = sizebuf*2;
	int socket_create(int domain=AF_INET, int type=SOCK_STREAM, int protocol=0);
	int connect(int fd, const char * addr, unsigned int port, short unsigned int domain=AF_INET);
	int bind(int fd, const char * addr="localhost", unsigned int port=0, short unsigned int domain=AF_INET);
	
	void write_sock(int fd, std::string msg);
	std::string read_sock(int fd, int max_size=maxsize);
}
