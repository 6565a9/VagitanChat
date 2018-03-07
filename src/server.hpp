#include"chat.hpp"
#include"sockets.hpp"

class Server : public chat{
	private:
		bool connecting(void) override;
	protected:
		
	public:
		Server(const char * host, unsigned int port);
		Server(void);
};
