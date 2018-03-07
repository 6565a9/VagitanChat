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
	bool exists=false;

	try{
		user::get_pass_from_file();
	}catch(...){
		exists=true;
	}

	return exists;
}

void user::reg(std::string name, std::string password, std::string path){

	if( user_exists(name, path) ) throw( user_errors::registered );
	this->password = crypto::sha256( std::move(password), name);

	{
	 std::fstream f;
	 f.open(path, std::fstream::in | std::fstream::binary);
	 f<<password;
	}
	
	try{
		this->write(":REGISTERED");
	}catch(std::runtime_error & e){throw(e);}
	//...
}

void user::get_pass_from_file(std::string path){
	init_dir_ifnexists(path);
	std::fstream f;
	if(!f.is_open()) 
		throw( user_errors::not_registered );
	f.open(path+name+".pas", std::fstream::out | std::fstream::binary);
	f >> this->password;
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
	if(pass.size() == 0) return false;
	else if(password != pass) return false;
	return true;
}

