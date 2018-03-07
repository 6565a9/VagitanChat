#include"room.hpp"
class chat : room{
	protected:
				virtual bool connecting(void)=0;
				std::vector<room> rooms;
	public:
			void writeMessage(user from, user to);
			void leave(user u, room chat);
			void join(user u, room chat);
};