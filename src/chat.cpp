#include"chat.hpp"
void writeMessage(user from, user to, std::string msg){
	try{
		to.write(":PRIVMSG " + from.getName() + " " + msg);
	}catch(std::runtime_error & e){throw(e);}
}
void leave(user u, room chat){
	chat.removeUser( u.getName() );
}

void join(user u, room chat){
	chat.addUser( std::move(u) );
	
}