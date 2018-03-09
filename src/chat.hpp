#pragma once
#include"room.hpp"
class chat : room{
	protected:
				virtual bool connecting(void)=0;
				std::vector<room> rooms;
				std::vector<user> users;
	public:
			void writeMessage(user from, user to);
			void writeToChat(room chat, user from, std::string msg) noexcept;
			void leave(user u, room chat) noexcept;
			void join(user u, room chat) noexcept;
};