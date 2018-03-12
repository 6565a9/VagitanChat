#pragma once
#include"NativeClient.hpp"


constexpr const char IRCClient_NickCMD[] = "NICK";
constexpr const char IRCClient_UserCMD[] = "USER";
constexpr const char IRCCLient_PrivmsgCMD[] = "PRIVMSG";
constexpr const char IRCCLient_JoinToRoomCMD[] = "JOIN";
constexpr const char IRCCLient_LeaveFromRoomCMD[] = "PART";
constexpr const char IRCCLient_PingCMD[] = "PING";
constexpr const char IRCCLient_Quit[] = "QUIT";

constexpr const char IRCCLient_Cap[] = "CAP";


class IRCClient : public NativeClient{
			std::string serv_name;
		private:
			typedef bool ( IRCClient :: *ClientFunc )( ClientFuncContext );
			bool Nick( ClientFuncContext ) noexcept;
			bool User ( ClientFuncContext ) noexcept override;
			bool Privmsg ( ClientFuncContext ) noexcept override;
			bool JoinToRoom( ClientFuncContext ) noexcept override;
			bool LeaveFromRoom( ClientFuncContext ) noexcept override;
			bool Ping( ClientFuncContext ) noexcept override;
			
			bool Cap (ClientFuncContext ) noexcept;
		private:
			bool Command( command_container&  ) override;
			

			void writeAsIRC(user & u, std::string msg){
				u.write(":"+serv_name+" "+msg);
			}
		private:
			using fnm = std::map<std::string, ClientFunc >;
			fnm  functions_client;
		 	//fnm functions_rooms;
		public:

			//type_command typeOfCommand(std::string command);
			IRCClient(std::vector<room> & room, std::vector<user> & user, std::string serv_name = "IRC-TEST");

};
