#include"chat.hpp"
#include <functional>
#include<sstream>

#define ClientFuncContext user u, std::stringstream && stream
#define RoomFuncContext room r, user u, std::stringstream && stream

#define COMMAND_ANY(TEXT,FUNC,WHAT)\
	{TEXT, [this](WHAT){this->FUNC(u, std::move(stream) ) ;}}

#define COMMAND_ROOM(TEXT, FUNC) COMMAND_ANY(TEXT,FUNC, RoomFuncContext)

#define COMMAND(TEXT, FUNC) COMMAND_ANY(TEXT,FUNC, ClientFuncContext)

using ClientFuncPtr = void (*)(ClientFuncContext);
using ClientFunc = void (ClientFuncContext);

class Client{
	public:
		std::map<std::string, std::function<ClientFunc> > functions;
};