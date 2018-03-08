#include"NativeClient.hpp"

void NativeClient::User(ClientFuncContext) noexcept{
	
}

void NativeClient::Register(ClientFuncContext) noexcept{
	
}

NativeClient::NativeClient(void){
			functions={
				  COMMAND(":USER", User),
				  COMMAND(":REGISTER", Register)
				};

}