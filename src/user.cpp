#include"user.hpp"
#include"util.hpp"

void user::init_dir_ifnexists( std::string path ) noexcept{
	DIR* dir = opendir( path.c_str() );
	if(!dir){ 
		mkdir(path.c_str(), 0777);
		closedir(dir); 
	}
}

bool user::user_exists(std::string name, std::string path) noexcept{
	bool exists=true;

	try{
		user::get_pass_from_file();
	}catch(...){
		exists=false;
	}

	return exists;
}

void user::reg(std::string name, std::string password, std::string path){
	this->name=name;

	if( user_exists(name, path) ) throw( user_errors::registered );
	if(name.size() < minsizename) throw( user_errors::smallname );
	else if(name.size() > maxnamesize) throw( user_errors::bigname );

	crypto::sha256( password, name);
	//std::cout << "Now password " << password;
	{
	 std::fstream f;
       f.open(path+name+".pas", std::fstream::out | std::fstream::binary);

	 if(!f.is_open()) {
		throw ( std::runtime_error("Cannot register, cannot create file") );
	 }
	 f<<password;
	}
	
	try{
		this->write(":REGISTERED");
	}catch(std::runtime_error & e){throw(e);}
	//...
}

void user::get_pass_from_file(std::string path){


	init_dir_ifnexists(path);
	//std::cout << path+name+".pas" << std::endl;
	std::ifstream f(path+name+".pas", std::ios::binary );
	
	if( !f.is_open() ) {
		std::cout << "File not opened" << std::endl;
		throw( user_errors::not_registered );
	}
	password="";
	std::string s;
	while( f >> s )		password=password+s;
	
}

void user::init_user(void){
	try{
		user::get_pass_from_file();
	}catch( std::runtime_error & e){
		throw(e);
	}
}

user::user(std::string && name, int && fd, bool isIRCUser) : name(name), fd(fd), isIRCUser(isIRCUser){
	init_user();
}

user::user(std::string name, int fd,  bool isIRCUser) : name(name), fd(fd), isIRCUser(isIRCUser){
	init_user();
}

user::user(std::string && name, std::string && password) : isIRCUser(false){
	reg(name, password);
}





bool user::checkpass(std::string pass) noexcept{
	/*
	std::cout << pass << std::endl;
	std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~";
	std::cout << password << std::endl;
	char * tmp, *tmp1;
	tmp = (char*)pass.c_str();
	tmp1 = (char*)password.c_str();
	while(*tmp && *tmp1){
		if(*tmp != *tmp1){
			std::cout << int(*tmp) << "!=" << int(*tmp1) << std::endl;
		}
		tmp++;
		tmp1++;
	}
	*/
	if(pass.size() == 0) return false;
	else if(password != pass) return false;
	return true;
}

