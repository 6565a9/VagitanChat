#include"NativeClient.hpp"


constexpr const char IRCClient_NickCMD[] = ":NICK";
constexpr const char IRCCLient_PrivmsgCMD[] = ":PRIVMSG";
constexpr const char IRCCLient_JoinToRoomCMD[] = ":JOIN";
constexpr const char IRCCLient_LeaveFromRoomCMD[] = ":PART";
constexpr const char IRCCLient_PingCMD[] = ":PING";
constexpr const char IRCCLient__Quit[] = ":QUIT";



class IRCClient : public NativeClient{

//		std::vector<room> & rooms_r;
//		std::vector<user> & users_r;
		private:
			typedef bool ( IRCClient :: *ClientFunc )( ClientFuncContext );
			bool Nick( ClientFuncContext ) noexcept;
			bool Privmsg ( ClientFuncContext ) noexcept override;
			bool JoinToRoom( ClientFuncContext ) noexcept override;
			bool LeaveFromRoom( ClientFuncContext ) noexcept override;
			bool Ping( ClientFuncContext ) noexcept override;
		private:
			using fnm = std::map<std::string, ClientFunc >;
			fnm  functions_client;
		 	fnm functions_rooms;
		public:

			//type_command typeOfCommand(std::string command);
			bool Command( command_container&  ) override;
			IRCClient(std::vector<room> & room, std::vector<user> & user);
			IRCClient() : //NativeClient()
					 users_r(null_references.u), rooms_r(null_references.r){};

};
