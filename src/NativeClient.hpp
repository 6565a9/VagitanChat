#include"Client.hpp"
class NativeClient : public Client{
	private:
		void User( ClientFuncContext ) noexcept;
		void Register( ClientFuncContext ) noexcept;
		void Privmsg ( ClientFuncContext ) noexcept;
		void JoinToRoom( RoomFuncContext ) noexcept;
		void LeaveFromRoom( RoomFuncContext ) noexcept;
	public:
		NativeClient(void);
};