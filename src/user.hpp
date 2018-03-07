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
		void init_user(std::string && name);
	protected:
		std::string name;
		std::string password;
		bool user_exists(std::string name, std::string path=default_user_dir) noexcept;
	public:
		user(std::string && name);
		user(std::string name);
		user(std::string && name, std::string && password);
		user()=default;
		std::string & getName(void) noexcept{return name;}
		bool checkpass(std::string) noexcept;
		virtual bool connecting(void)=0;
};
