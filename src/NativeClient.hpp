#include"chat.hpp"

#include <functional>
#include<sstream>

#define ClientFuncContext user & u, std::vector<std::string> && stream
#define RoomFuncContext room & r, user & u, std::vector<std::string> && stream

constexpr const char NativeClient_UserCMD[] = ":USER";
constexpr const char NativeClient_RegisterCMD[] = ":REGISTER";
constexpr const char NativeClient_PrivmsgCMD[] = ":PRIVMSG";
constexpr const char NativeClient_JoinToRoomCMD[] = ":JOIN";
constexpr const char NativeClient_LeaveFromRoomCMD[] = ":LEAVE";
constexpr const char NativeClient_PingCMD[] = ":PING";


struct command_container{
	std::string text;
	user & u;
	room & r;
};

enum class type_command{
		client, room, undefined
};

class NativeClient{
	typedef bool (NativeClient::*ClientFunc )(ClientFuncContext);
	typedef bool (NativeClient::*RoomFunc)(RoomFuncContext);
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
		bool JoinToRoom( RoomFuncContext ) noexcept;
		bool LeaveFromRoom( RoomFuncContext ) noexcept;
		bool Ping( ClientFuncContext ) noexcept;
	

	private:
		std::map<std::string, ClientFunc > functions_client;
		std::map<std::string, RoomFunc > functions_room;
	private:
	public:
		virtual bool try_connect(int fd, std::string);
		//bool find_command(std::string && command, type_command type);
		virtual type_command typeOfCommand(std::string command);
		virtual bool Command(command_container & contain);
		virtual void erase(int fd){
			
		}
	public:
		bool NotNative;

		NativeClient(std::vector<room> & room, std::vector<user> & user );
};
