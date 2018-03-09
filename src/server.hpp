#include"chat.hpp"
#include"user.hpp"
#include"sockets.hpp"
#include<thread>

constexpr unsigned int maxForPeer=3;

class Server : public chat{
	private:
		int fd;
		unsigned long maxConnections;
	private:
		bool connecting(void) override;
		void client_thread(int fd);
	private:
		std::vector<std::string> connected;
		std::vector<std::thread> threads;

	protected:
		
	public:
		Server(const char * host, unsigned int port, unsigned long MaxConnections=30);
		Server(void) = delete;
		~Server(void);
};