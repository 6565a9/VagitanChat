#include"server.hpp"

bool Server::connecting(void) {
	while(1){

		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		socklen_t c_len = sizeof(addr);

		int user = accept(this->fd, (sockaddr*)&addr, &c_len);
		std::string ip = inet_ntoa(addr.sin_addr);
		std::cout << "connected from " << ip << std::endl;

		std::string msg = Sockets::read_sock(user);
				
			
		Sockets::write_sock(user, ":Welcome\n");
		
		close(user);
	}
}

Server::~Server(){
	if(this->fd)
		close(this->fd);
}

Server::Server(const char * host, unsigned int port, unsigned long maxConnections)
		: maxConnections(maxConnections){

	try{
		fd =Sockets::socket_create();

		Sockets::bind(fd,host, port);
		listen(fd, maxConnections);
		std::cout << "start thread for listening" << std::endl;

		std::thread(&Server::connecting, this).join();
		
	}catch(std::runtime_error & e){
		std::cerr << e.what() << std::endl;
		throw( std::runtime_error("\nTry other port/address") );
	}
}