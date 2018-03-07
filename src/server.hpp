#include"room.hpp"
#include"sockets.hpp"

class Server : public room{
	private:
		bool connecting(void) override;
	public:
		Server(const char * host, unsigned int port);
		Server(void);
};
