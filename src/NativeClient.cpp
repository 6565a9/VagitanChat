#include"NativeClient.hpp"
#include"util.hpp"



bool NativeClient::User(ClientFuncContext) noexcept{
	try{
		if( NotEnought(3, stream.size(), u ) ) return false;
		u.getName() = stream[1];
		if(!u.is_exists()){
			u.write(":ERROR not registered\n");
			return false;
				
		}
		u.get_pass_from_file();
		crypto::sha256(stream[2],stream[1]);
		//std::string pass = crypto::sha256(std::move(stream[2]), stream[1]);
		if(!u.checkpass(stream[2])){
			u.write(":ERROR uncorrect password\n");
			return false;			
		}
		u.write(":WELCOME "+stream[1]+"\n");
		logined=true;
		return true;
	}catch(...){}
	return false;
}

bool NativeClient::Register(ClientFuncContext) noexcept{
	try{
		if( NotEnought(3, stream.size(), u ) ) return false;
		try{
			u.reg(stream[1], stream[2]);
			logined=true;
			return true;
		}catch(std::runtime_error & e){
			std::cerr << e.what() << std::endl;
		}
	}catch(user_errors & e){
		switch(e){
			case user_errors::smallname:
				u.write(":ERROR SmallName");
				break;
			case user_errors::registered:
				u.write(":ERROR Registered");
				break;
		}
	}
	return false;
}

bool NativeClient::Privmsg ( ClientFuncContext ) noexcept{
	
}

bool NativeClient::JoinToRoom( RoomFuncContext ) noexcept{
	
}

bool NativeClient::LeaveFromRoom( RoomFuncContext ) noexcept{
	
}

bool NativeClient::Ping( ClientFuncContext ) noexcept{
	if(!logined) return false;
	u.write(":WRITEANYATEXT ");
	u.write("\n"+u.read());
}

//TODO:
type_command NativeClient::typeOfCommand(std::string command){
	try{
		functions_client.at(command);
		return type_command::client;
	}catch(std::out_of_range & e){
		try{
			functions_room.at(command);
			return type_command::room;			
		}catch(std::out_of_range & e){
			NotNative=true;
			return type_command::undefined;
		}
	}
}

bool NativeClient::try_connect(int fd){
		room r;
		user u(fd);
		bool res;
		do{
			std::string msg = Sockets::read_sock(fd);
			Text::deleteChar((char*)msg.c_str());
			command_container contain={std::move(msg),u, r};
			res = Command(contain);
		}while(res && logined);
}

bool NativeClient::Command(command_container & contain){
	std::vector<std::string> msgs = Text::split(contain.text, ' ');
	type_command type = typeOfCommand(msgs[0]);
	std::cout << "Getted type " << int(type) << std::endl;
	if(type == type_command::undefined) return false;

	switch(type){
		case type_command::room:
			return (this->*(functions_room[msgs[0]])) (contain.r, contain.u, std::move(msgs));
			break; // not need but let be 
		case type_command::client:
			return (this->*(functions_client[msgs[0]])) (contain.u, std::move(msgs));
			break;
	}
}


NativeClient::NativeClient(void){
			functions_client[NativeClient_UserCMD] = &NativeClient::User;
			functions_client[NativeClient_RegisterCMD] = &NativeClient::Register; 
			functions_client[NativeClient_PrivmsgCMD] = &NativeClient::Privmsg;
			functions_client[NativeClient_PingCMD] = &NativeClient::Ping;

			//
			functions_room[NativeClient_JoinToRoomCMD] = &NativeClient::JoinToRoom;
			
			functions_room[NativeClient_LeaveFromRoomCMD] = &NativeClient::LeaveFromRoom;
}