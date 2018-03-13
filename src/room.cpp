#include"room.hpp"

bool room::addUser(user & u) noexcept{
	if(userExists(u.getName())){
		u.write(":ERROR ALREADY ADDED");
		return false;
	}
	users[ u.getName() ] = &u;
	//std::cout << u.getName() << " added\n" << users.size() << "\n";

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
	for(auto it = users.cbegin(); it!=users.cend(); it++){
		if(it->first == name ){
			write_to_all(":REMOVED "+name+" "+std::string(this->name));
			users.erase( it );

			return true;
		}
	}

	return false;
}

bool room::userExists(std::string name) noexcept{
	for(auto it = users.cbegin();it!=users.cend();it++){
		//std::cout << it->first <<"!="<<name<<std::endl;
		if(it->first == name) return true;
	}
	return false;
}

void room::write_to_all(std::string msgNative, std::string msgIRC) noexcept{
	//std::cout << " write for all " << msgNative << std::endl;
	for(auto u : this->users){
		try{
			if(msgIRC.size() && u.second->IRCUser()){
				std::cout << "Write IRC";
				u.second->write(msgIRC);
			}
			else
				u.second->write(msgNative);
		}catch(...){
			removeUser(u.first);	
		}
	}
}
