#ifndef JFS_DANGEROUSROOM_H
#define JFS_DANGEROUSROOM_H
#include "room.h"
#include "actor.h"
namespace labb3{
	class DangerousRoom : public Room{
		int _damage; 
	public:
		DangerousRoom();
		DangerousRoom(std::string);
		virtual ~DangerousRoom();
		virtual bool interact(Actor* player);
		int getDamage()const;
		virtual bool isFriendly();
	};
	
}
#endif
