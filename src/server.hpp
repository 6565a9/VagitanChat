#include"chat.hpp"
#include"user.hpp"
#include"sockets.hpp"
#include<thread>

class Server : public chat{
	private:
		bool connecting(void) override;
		int fd;
		unsigned long maxConnections;
		std::vector<std::string> connected;
		
	protected:
		
	public:
		Server(const char * host, unsigned int port, unsigned long MaxConnections=30);
		Server(void) = delete;
		~Server(void);
};