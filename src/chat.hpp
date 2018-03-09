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
	
	static void writeToChat(room chat, user from, std::string msg, std::string ircmsg="") {
		chat.write_to_all(":PRIVMSG @" + chat.getName() + " " + from.getName() + " "+msg);
	}
}