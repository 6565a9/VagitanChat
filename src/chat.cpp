#include"chat.hpp"
void writeMessage(user from, user to, std::string msg){
	try{
		to.write(":PRIVMSG " + from.getName() + " " + msg);
	}catch(std::runtime_error & e){throw(e);}
}

void writeToChat(room chat, user from, std::string msg) noexcept{
	chat.write_to_all(":PRIVMSG " + chat.getName() + " " + from.getName() + " "+msg);
}

void leave(user u, room chat) noexcept{
	chat.removeUser( u.getName() );
}

void join(user u, room chat) noexcept{
	chat.addUser( std::move(u) );
}
