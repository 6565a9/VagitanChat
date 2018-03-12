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


	static void quit(user who, std::vector<room> & rooms){
		try{
			for(auto r : rooms)
				if(r.userExists(who.getName())){
					r.removeUser( std::move( who.getName() ) );
					//TODO: IRC PROTOCOL
					r.write_to_all(":QUIT @" + r.getName() + " " + who.getName() + " LEAVING");
				}
		}catch(...){}
	}
}
