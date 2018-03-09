#include"chat.hpp"

#include <functional>
#include<sstream>

#define ClientFuncContext user & u, std::vector<std::string> && stream
//#define RoomFuncContext room & r, user & u, std::vector<std::string> && stream

constexpr const char NativeClient_UserCMD[] = ":USER";
constexpr const char NativeClient_RegisterCMD[] = ":REGISTER";
constexpr const char NativeClient_PrivmsgCMD[] = ":PRIVMSG";
constexpr const char NativeClient_JoinToRoomCMD[] = ":JOIN";
constexpr const char NativeClient_LeaveFromRoomCMD[] = ":LEAVE";
constexpr const char NativeClient_PingCMD[] = ":PING";


struct command_container{
	std::string text;
	user & u;
//	room & r;
};


enum class type_command{
		client, room, undefined
};

class NativeClient{
	typedef bool (NativeClient::*ClientFunc )(ClientFuncContext);
	//typedef bool (NativeClient::*RoomFunc)(RoomFuncContext);
	private:
		std::vector<room> & rooms_r;
		std::vector<user> & users_r;
		bool logined;
	private:
		inline bool NotEnought(std::size_t nsize, std::size_t size, user & u ){
			if(nsize > size)
			{
				u.write(":ERROR not enought params\n");
				return true;
			}else if(nsize < size){
				u.write(":ERROR much params\n");
				return true;	
			}
			return false;
		}
		bool User( ClientFuncContext ) noexcept;
		bool Register( ClientFuncContext ) noexcept;
		bool Privmsg ( ClientFuncContext ) noexcept;
		bool JoinToRoom( ClientFuncContext ) noexcept;
		bool LeaveFromRoom( ClientFuncContext ) noexcept;
		bool Ping( ClientFuncContext ) noexcept;
	

	private:
		using fnm = std::map<std::string, ClientFunc >;
		 fnm  functions_client;
		 fnm functions_rooms;
	private:
		decltype(auto) find_room(std::string name){
			for(auto & room : rooms_r){
				if(room.getName() == name) return (room);
			}
		}
		decltype(auto) find_user(std::string name){
			for(auto & user : users_r){
				if(user.getName() == name) return (user);
			}
		}
	public:
		virtual bool try_connect(int fd, std::string);
		//bool find_command(std::string && command, type_command type);
		virtual type_command typeOfCommand(std::string command);
		virtual bool Command( command_container&  );
		virtual void erase(int fd){
			
		}
	public:
		bool NotNative;

		NativeClient(std::vector<room> & room, std::vector<user> & user );
};
