#pragma once
#include"sockets.hpp"
#include <fstream> 
#include <dirent.h>
#include <sys/stat.h>
#include<chrono>

constexpr const char* default_user_dir="./users/";

constexpr std::size_t minsizename = 4;
constexpr std::size_t maxnamesize = 28;


enum class user_errors{
	registered, not_registered, smallname, bigname
};

class user{
	private:
		void init_dir_ifnexists( std::string path ) noexcept;
		void init_user(void);
		int fd;
		std::chrono::steady_clock::time_point entering_time, reg_time;
		bool registered=false;
	protected:
		std::string name;
		std::string password;
		bool user_exists(std::string name, std::string path=default_user_dir) noexcept;
		bool isIRCUser;
	public:
		friend bool operator==(const user u1, const user u2){
			if(u1.fd == u2.fd) return true;
			else if(u1.name == u2.name) return true;
			return false;
		}

		inline auto getEnterTime(){
			return entering_time;
		}

		inline auto getRegTime(){
			return reg_time;
		}
		inline auto isRegistered(){
			return registered;
		}

		explicit user(std::string && name, int && fd, bool isIRCUser=false);
		explicit user(std::string name, int fd, bool isIRCUser=false) ;
		explicit user(std::string && name, std::string && password);
		user(int fd) : fd(fd){}
		void reg(std::string name, std::string password, std::string path=default_user_dir);
		void deleteF(std::string path=default_user_dir);
		inline void close_connect(std::string reason){
			this->write(":CLOSED " + reason);
		}
		bool is_exists(std::string path=default_user_dir){
			return user_exists(this->name,path);
		}
		void get_pass_from_file(std::string path=default_user_dir);

		bool IRCUser(){
			return isIRCUser;
		}
		void setFD(int fd){
			this->fd=fd;
		}
	
		user()=default;

		std::string & getName(void) noexcept{return name;}
		std::string & getPass(void) noexcept{return password;}

		bool checkpass(std::string) noexcept;
		
		void write(std::string msg){
			try{
				Sockets::write_sock(this->fd, msg+"\n");
			}catch(std::runtime_error & e){
				close(this->fd);
				this->fd=0;
				throw(e);
			}
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
