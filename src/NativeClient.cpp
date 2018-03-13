#include"NativeClient.hpp"
#include"util.hpp"



bool NativeClient::User(ClientFuncContext) noexcept{
	try{
		if( NotEnought(3, stream.size(), u ) ) return false;
		if( !Text::correct_name(stream[1].c_str()) ) return false;
		u.getName() = stream[1];
		if(!u.is_exists()){
			u.write(":ERROR not registered");
			return false;
				
		}
		u.get_pass_from_file();
		crypto::sha256(stream[2],stream[1]);
		//std::string pass = crypto::sha256(std::move(stream[2]), stream[1]);
		if(!u.checkpass(stream[2])){
			u.write(":ERROR uncorrect password");
			return false;			
		}
		
		for(auto it = std::cbegin(users_r);it!=users_r.cend();it++)
			if(*it == u){
				u.write(":ERROR nickname busy");
				return false;
			}
			
		u.write(":WELCOME "+stream[1]);
		users_r.push_back(u);
		logined=true;
		return true;
	}catch(...){}
	return false;
}

bool NativeClient::Register(ClientFuncContext) noexcept{
	try{
		if( NotEnought(3, stream.size(), u ) ) return false;
		if( !Text::correct_name(stream[1].c_str()) ) return false;
		try{
			u.reg(stream[1], stream[2]);
			logined=true;
			users_r.push_back(u);
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
	//:RRIVMSG ROOM/USER MSG
	if(!logined) return false;
	if( stream.size() < 3 ) return false;
	std::ostringstream msgs;
	for(auto it = std::cbegin(stream)+2;it!=stream.cend();it++)
			msgs << " "<< *it;

	
	if(stream[1].c_str()[0] != '@' ){
		for(auto usr : users_r)
			if(usr.getName() == stream[1])
				try{
					std::cout << msgs.str() << std::endl;
					ChatFuncs::writeMessage( u , usr, msgs.str() );
					return true;
				}catch(std::runtime_error & e){
					Quiting(usr);
					u.write(std::string(":ERROR ") + e.what());
				}

		
		u.write(":ERROR NOT FOUND");
	}else{
		const char * tmp = (stream[1].c_str()+1);
		for(auto & room : rooms_r){
			if(strcmp( tmp, room.getName().c_str() ) == 0 )
			{
				if( !room.userExists(u.getName()) ){
					u.write(":ERROR NOT JOINED TO ROOM "+stream[1]);
					return true;
				}
				ChatFuncs::writeToChat(room,u, msgs.str());
				return true;
			}
		}
		//std::cout << "Not found room\n";
		u.write(":ERROR NOT FOUND ROOM "+stream[1]);

	}
	return true;

}

bool NativeClient::JoinToRoom( ClientFuncContext ) noexcept{
	if(!logined) return false;
	if( stream.size() < 2 ) return false;
	if( !Text::correct_name(stream[1].c_str()) ) return false;

	for(auto & room : rooms_r)
			if(room.getName() == stream[1]){
				room.addUser(u);
				return true;
			}
	//rooms_r.push_back({stream[1]});
	room rtmp(stream[1]);
	u.write(":ROOM " +stream[1]+ " CREATED");
	rtmp.addUser(u);
	std::cout << "User added\n";
	rooms_r.push_back(rtmp);
	return true;
}

bool NativeClient::LeaveFromRoom( ClientFuncContext ) noexcept{
	if(!logined) return false;
	if( stream.size() < 2 ) return false;
	if( !Text::correct_name(stream[1].c_str()) ) return false;

	for(auto & room : rooms_r)
			if(room.getName() == stream[1]){
				if(!room.removeUser(u.getName())){
					u.write(":ERROR NOT JOINED");
					return true;
				}
				if(room.user_count() == 0)
				 for(auto it = rooms_r.begin();it!=rooms_r.end();it++)
					if(it->getName() == stream[1]){
					rooms_r.erase(it);
					return true;
				 }
				return true;
			}
	u.write(":ERROR undefined room");
	return true; // todo
	
}

bool NativeClient::Ping( ClientFuncContext ) noexcept{
	if(!logined) return false;
	u.write(":WRITEANYATEXT ");
	u.write(u.read());
}

//TODO:
type_command NativeClient::typeOfCommand(std::string command){
	try{
		functions_client.at(command);
		return type_command::client;
	}catch(std::out_of_range & e){
			//NotNative=true;
			return type_command::undefined;
	}
}

bool NativeClient::funcExists(std::string func){
	return	typeOfCommand(func) == type_command::undefined ? false : true;
}

bool NativeClient::try_connect(int fd, std::string msg){
		user u(fd);

		do{
			std::vector<std::string> msgs = Text::split(msg, '\n');
			for(auto m : msgs){
				const auto starting_without_space = msg.find_first_not_of(' ');
				if(starting_without_space-msg.find_last_not_of(' ')!=0)
					msg = msg.substr(starting_without_space, starting_without_space-msg.find_last_not_of(' '));
			
				command_container contain={msg,u};

				if(  !Command(contain) || this->error_cmd > max_error_cmd){
					 if(this->error_cmd > max_error_cmd) {
						Quiting(u);
						return false;
					 }
					 this->error_cmd++;
				}else this->error_cmd=0;
			}

			try{
				msg = Sockets::read_sock(fd);
			}catch(...){
				break;
			}
		}while( logined );
		Quiting(u);
}

bool NativeClient::Command(command_container & contain){
		std::cout << "Native FUNC: " << contain.text << std::endl;
		return Commands::Command(this, functions_client, contain); // TODO:
}


bool NativeClient::Quit( ClientFuncContext ) noexcept{
	error_cmd=max_error_cmd+1;
	logined = false;
	return false;
}


NativeClient::NativeClient(std::vector<room> & room, std::vector<user> & user):
			users_r(user),rooms_r(room)

{
			functions_client[NativeClient_UserCMD] = &NativeClient::User;
			functions_client[NativeClient_RegisterCMD] = &NativeClient::Register; 
			functions_client[NativeClient_PrivmsgCMD] = &NativeClient::Privmsg;
			functions_client[NativeClient_PingCMD] = &NativeClient::Ping;
			functions_client[NativeClient_Quit] = &NativeClient::Quit;

			//
			functions_client[NativeClient_JoinToRoomCMD] = &NativeClient::JoinToRoom;
			
			functions_client[NativeClient_LeaveFromRoomCMD] = &NativeClient::LeaveFromRoom;
}
