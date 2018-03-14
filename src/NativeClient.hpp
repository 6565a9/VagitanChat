#pragma once
#include"chat.hpp"
#include"util.hpp"
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
constexpr const char NativeClient_Quit[] = ":QUIT";
constexpr const char NativeClient_List[] = ":LIST";

constexpr char max_error_cmd = 3;



struct command_container{
	std::string text;
	user & u;
//	room & r;
};


enum class type_command{
		client, /*room,*/ undefined
};

namespace Commands{
	//TODO:
	template <typename Obj>
	type_command typeOfCommand(std::string command, Obj obj);
	template <typename Obj> 
	bool Command(command_container & contain, Obj obj);
}

class NativeClient{
	typedef bool (NativeClient::*ClientFunc )(ClientFuncContext);
	//typedef bool (NativeClient::*RoomFunc)(RoomFuncContext);
	protected:
		std::vector<room> & rooms_r;
		std::vector<user> & users_r;
		bool logined;


	protected:

		type_command typeOfCommand(std::string command);




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

		virtual bool User( ClientFuncContext ) noexcept;
		virtual bool Register( ClientFuncContext ) noexcept;
		virtual bool Privmsg ( ClientFuncContext ) noexcept;
		virtual bool JoinToRoom( ClientFuncContext ) noexcept;
		virtual bool LeaveFromRoom( ClientFuncContext ) noexcept;
		virtual bool Ping( ClientFuncContext ) noexcept;
		virtual bool Quit( ClientFuncContext ) noexcept;
		virtual bool List( ClientFuncContext ) noexcept;
	protected:
		//template <typename Obj>  bool Command(command_container & contain, Obj obj);	
		//template <typename Obj>  type_command typeOfCommand(std::string command, Obj obj);
		bool funcExists(std::string);
	private:
		
	private:
		using fnm = std::map<std::string, ClientFunc >;
		 fnm  functions_client;
		 //fnm functions_rooms;
	protected:
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
		inline void Quiting(user & u){
			std::cout << "quiting " << u.getName() << std::endl;
			for(auto it = std::cbegin(users_r);it!=users_r.cend();it++)
			if(*it == u){
				ChatFuncs::quit(*it, rooms_r);
				users_r.erase(it);
				break;
			}
		}
	public:
		bool try_connect(int fd, std::string);
		//bool find_command(std::string && command, type_command type);
		virtual bool Command( command_container&  );
		//virtual void erase(int fd);

		bool getLogined(void){
			return logined;
		}

		char error_cmd ;
	public:
//		bool NotNative;
		//NativeClient(void)=default;
		NativeClient(std::vector<room> & room, std::vector<user> & user );
	public:
			template <typename Obj, typename Map, typename User> 
				friend bool Command(Obj obj, Map map, std::string cmd, User u );
			template <typename Map> bool funcExists(Map map, std::string name){
				try{
					map.at(name);
					return true;
				}catch(std::out_of_range & e){
					return false;
				}
			}

};
namespace Commands{
	template <typename Obj, typename Map> 
	bool Command(Obj obj, Map map, command_container & contain){
		std::vector<std::string> msgs = Text::split(contain.text, ' ');
		if( !obj->funcExists(map, msgs[0]) ) return false;
		//return (obj->*(obj->functions_client[cmd])) (u, std::move(cmd));
		return (obj->*(map[ msgs[0] ])) (contain.u, std::move(msgs));		
	}

}

