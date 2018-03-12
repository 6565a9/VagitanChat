#include"IRCClient.hpp"
//TODO:

bool IRCClient :: Nick( ClientFuncContext ) noexcept{
	/*
		:NICK NickName
		:USER ... -> IGNORE 
	*/

	if( NotEnought(2, stream.size(), u ) ) return false;
	u.getName() = stream[1];
	logined=true; // for a while
	writeAsIRC(u,"Nick was set");
	return true;
}


bool IRCClient :: Privmsg( ClientFuncContext ) noexcept{

}

bool IRCClient :: JoinToRoom( ClientFuncContext ) noexcept{
	if( NotEnought(2, stream.size(), u ) ) return false;
	
	return true;
}

bool IRCClient :: LeaveFromRoom( ClientFuncContext ) noexcept{
	return false;
}

bool IRCClient :: Ping( ClientFuncContext ) noexcept{
	return true;
}

bool IRCClient::User( ClientFuncContext ) noexcept{
	//USER user user 127.0.0.1 :realname

	return true;
}

bool IRCClient::Cap (ClientFuncContext ) noexcept{
	if(stream.size() > 2 && stream[1] == "LS")
		writeAsIRC(u,"");
	return true;
}



bool IRCClient::Command(command_container & contain){
		std::cout << "IRC FUNC: " << contain.text << std::endl;
		return Commands::Command(this, functions_client, contain); // TODO:
}


IRCClient::IRCClient(std::vector<room> & room, std::vector<user> & user , std::string serv_name):
		NativeClient(room,user), serv_name(serv_name){
			functions_client[IRCClient_NickCMD] = &IRCClient::Nick;
			functions_client[IRCCLient_PrivmsgCMD] = &IRCClient::Privmsg;
			functions_client[IRCCLient_JoinToRoomCMD] = &IRCClient::JoinToRoom;
			functions_client[IRCCLient_Quit] = &IRCClient::Quit;
			functions_client[IRCCLient_PingCMD] = &IRCClient::Ping;
			functions_client[IRCClient_UserCMD] = &IRCClient::User;
			functions_client[IRCCLient_Cap] = &IRCClient::Cap;
			//
			functions_client[IRCCLient_JoinToRoomCMD] = &IRCClient::JoinToRoom;
			functions_client[IRCCLient_LeaveFromRoomCMD] = &IRCClient::LeaveFromRoom;	
}
