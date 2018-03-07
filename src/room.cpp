#include"room.hpp"

bool room::addUser(user && u) noexcept{
	if(userExists(name)) return false;
	users[ u.getName() ] = u;
	/*
	try{
		u.write(":ADDED "+std::string(this->name));
	}catch(...){return false;}
	*/
	write_to_all(":ADDED "+u.getName()+" "+std::string(this->name));
	return true;
}

bool room::removeUser(std::string name) noexcept{
	if(!userExists(name)) return false;
	write_to_all(":REMOVED "+users[name].getName()+" "+std::string(this->name));
	users.erase( name );
	return true;
}

bool room::userExists(std::string name) noexcept{
//	for(auto u : this->users){if(u.first == name) return true;}
	try{
		users["name"];
	}catch(std::out_of_range & e){
		return false;
	}
	return false;
}

void room::write_to_all(std::string msgNative, std::string msgIRC) noexcept{
	for(auto u : this->users){
		try{
			if((void*)&msgIRC!=nullptr && u.second.IRCUser())
				u.second.write(msgIRC);
			else
				u.second.write(msgNative);
		}catch(...){}
	}
}