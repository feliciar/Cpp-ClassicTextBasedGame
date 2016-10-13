#ifndef JFS_GAME_H
#define JFS_GAME_H
#include "room.h"
#include "actor.h"
#include "player.h"
#include "item.h"
#include "itemfile.h"
#include "weapon.h"
#include "dangerous.h"
#include "friendly.h"
#include "dangerousRoom.h"
#include "friendlyRoom.h"
#include <vector>
#include <map>

namespace labb3{
	class Room;
	class Player;
	class Game{
			Player _player;
			Room* _currentRoom;
			std::vector<Room*> _rooms;
			ItemFile * _item;
			std::pair<Room*, Room*> _disapearingDoor; 
			
		public: 
			bool win = false;
			//static std::map<std::string, Item*> _items;
			//static std::map<std::string, Item*> getItems();
			Game();
			~Game();
			bool init();
		
			bool update();
			std::string readCommand()const;
			bool performCommand(std::string, Actor*);
		
			bool pickUp(std::string, Actor*);
			bool search();
			bool go(std::string, Actor*);
			bool hit(std::string, Actor*);
			bool lookAt(std::string)const;
			bool sleep(std::string);
			bool talkTo(std::string, Actor*);
			void actRandom(Actor*);
			Player* getPlayer();
			std::string printWelcome()const;
			std::string printCommands()const;
		private: 
			bool commandMatches(std::vector<std::string> words, std::vector<std::string> commandToMatch, int wordCount)const;
			std::string appendSubArrayToString(std::vector<std::string> array, int position)const;
		
	};
	
	
}
#endif
