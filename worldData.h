#ifndef JFS_WORLDDATA_H
#define JFS_WORLDDATA_H
#include "player.h"
#include "room.h"
#include "friendlyRoom.h"
#include "dangerousRoom.h"

namespace labb3{
	class Room;
	class Player;
	class WorldData{
		public: 
			Room* initWorld(std::vector<Room*> * rooms, Player* player, std::pair<Room*, Room*>* door);
	};
}
#endif