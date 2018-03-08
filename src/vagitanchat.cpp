#include"server.hpp"

int main(int argc, char ** arguments){
	if(argc < 3){
		std::cerr << arguments[0] << " host port" << std::endl;
		return 0;
	}
	try{
		Server serv(arguments[1], atoi(arguments[2]));
	}catch(std::runtime_error & e){
		std::cerr << e.what() << std::endl;
	}
}