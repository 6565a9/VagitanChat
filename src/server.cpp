#include"server.hpp"
#include"util.hpp"
#include"NativeClient.hpp"

void Server::client_thread(int fd){
            
            NativeClient nc(rooms,users);
            try{
		//std::cout << msg << " native command try" << std::endl;
		//bool r = nc.Command({std::move(msg),{fd}});
		std::string msg = Sockets::read_sock(fd);
		//if(!r && NotNative);// TODO: try IRC
		bool r = nc.try_connect(fd, msg);
                        
            }catch(...){}

		close(fd);

}


bool Server::connecting(void) {
	while(1){

		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		socklen_t c_len = sizeof(addr);

		int user = accept(this->fd, (sockaddr*)&addr, &c_len);
		std::string ip = inet_ntoa(addr.sin_addr);
		unsigned int c =0 ;
		std::cout << "connected from " << ip << std::endl;
		
		for(auto a : connected)
			if(a == ip) c++;
		if(c >= maxForPeer){
				Sockets::write_sock(user,":ERROR MAX CONNECTIONS\n");
				close(user);
				continue;
		}
		threads.push_back( std::thread(&Server::client_thread, this, user) );
		//std::cout << "\nThread" <<std::endl;
		//Sockets::write_sock(user, ":Welcome\n");
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
