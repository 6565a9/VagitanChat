#pragma once
#include"user.hpp"
#include<vector>
#include<map>


//TODO:...
enum class room_types{
	guest=(1<<1),
	voice=(1<<2),
	moderator=(1<<3),
	admin=(1<<4)
};

class room : public user{
	private:
		//std::vector<std::string> users;
		std::map<std::string, user*> users;
		std::string name;
	public:
		std::string & getName(void) noexcept{
			return name;
		}
		room(void)=default;
		room(std::string name) : name(name){}
		bool addUser(user & u) noexcept;
		bool removeUser(std::string name) noexcept;
		bool userExists(std::string name) noexcept;
		void write_to_all(std::string msgNative, std::string msgIRC="") noexcept;
		size_t user_count(void){
			return users.size();
		}
};