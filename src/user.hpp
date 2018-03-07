#include"sockets.hpp"
#include <fstream> 
#include <dirent.h>
#include <sys/stat.h>


constexpr const char* default_user_dir="./users/";
enum class user_errors{
	registered, not_registered
};

class user{
	private:
		void init_dir_ifnexists( std::string path ) noexcept;
		void reg(std::string name, std::string password, std::string path=default_user_dir);
		void get_pass_from_file(std::string path=default_user_dir);
		void init_user(void);
		int fd;
	protected:
		std::string name;
		std::string password;
		bool user_exists(std::string name, std::string path=default_user_dir) noexcept;
		bool isIRCUser;
	public:
		explicit user(std::string && name, int && fd, bool isIRCUser=false);
		explicit user(std::string name, int fd, bool isIRCUser=false) ;
		explicit user(std::string && name, std::string && password);
		bool IRCUser(){
			return isIRCUser;
		}
		~user(){
			this->write(":CLOSED");
			if(this->fd) close(this->fd);
		}
		user()=default;
		std::string & getName(void) noexcept{return name;}
		bool checkpass(std::string) noexcept;
		void write(std::string msg){
			Sockets::write_sock(this->fd, msg);
		}
		std::string read(){
			try{
				return Sockets::read_sock(this->fd);
			}catch(std::runtime_error & e){
				close(this->fd);
				this->fd=0;
				throw(e);
			}
		}	
};
