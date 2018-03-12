#include"IRCClient.hpp"


bool IRCClient :: Nick( ClientFuncContext ) noexcept{
	/*
		:NICK NickName
		:USER ... -> IGNORE 
		:PING aswdfiasdfuweriuasdfguawreygasfd
		:PONG aswdfiasdfuweriuasdfguawreygasfd
	*/
	return false;
}


bool IRCClient :: Privmsg( ClientFuncContext ) noexcept{
	return false;
}

bool IRCClient :: JoinToRoom( ClientFuncContext ) noexcept{
	return false;
}

bool IRCClient :: LeaveFromRoom( ClientFuncContext ) noexcept{
	return false;
}

bool IRCClient :: Ping( ClientFuncContext ) noexcept{
	return false;
}


IRCClient::IRCClient(std::vector<room> & room, std::vector<user> & user):
		rooms_r(room), users_r(user){
			functions_client[IRCClient_NickCMD] = &IRCClient::Nick;
			functions_client[IRCCLient_PrivmsgCMD] = &IRCClient::Privmsg;
			functions_client[IRCCLient_JoinToRoomCMD] = &IRCClient::JoinToRoom;
			functions_client[IRCCLient__Quit] = &IRCClient::Quit;
			functions_client[IRCCLient_PingCMD] = &IRCClient::Ping;
			//
			functions_client[IRCCLient_JoinToRoomCMD] = &IRCClient::JoinToRoom;
			functions_client[IRCCLient_LeaveFromRoomCMD] = &IRCClient::LeaveFromRoom;	
}
