#ifndef JFS_FRIENDLY_ROOM_H
#define JFS_FRIENDLY_ROOM_H
#include "room.h"
#include "actor.h"
namespace labb3{
	class FriendlyRoom : public Room{
		int _healingPower; 
	public:
		FriendlyRoom();
		FriendlyRoom(std::string);
		
		virtual ~FriendlyRoom();
		virtual bool interact(Actor* player);
		virtual bool isFriendly();
	};
	
}
#endif
