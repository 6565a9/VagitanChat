#pragma once
#include"room.hpp"
class chat : room{
	protected:
				virtual bool connecting(void)=0;
				std::vector<room> rooms;
				std::vector<user> users;
	public:
};

namespace ChatFuncs{
	static void writeMessage(user from, user to, std::string msg){
		try{
			to.write(":PRIVMSG " + from.getName() + " " + msg);
			}catch(std::runtime_error & e){throw(e);}
	}
	
	static void writeToChat(room chat, user from, std::string msg) {
		chat.write_to_all(":PRIVMSG " + chat.getName() + " " + from.getName() + " "+msg);
	}
	
	static void leave(user u, room chat) {
		chat.removeUser( u.getName() );
	}

	static void join(user u, room chat) {
		chat.addUser( std::move(u) );
	}
}