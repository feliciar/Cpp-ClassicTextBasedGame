#ifndef JFS_ROOM_H
#define JFS_ROOM_H
#include "itemfile.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include "actor.h"
#include "item.h"
#include "dangerous.h"
#include "player.h"
#include "friendly.h"
namespace labb3{
	class Room{
		
		protected: 
		
		std::vector<std::string> _items;
		std::vector<Actor*> _actors;
		std::vector<Room*> _doors;
		std::string _description;	
		
		public:
		
		Room();
		Room(std::string);
		virtual ~Room();
		virtual bool interact(Actor* player) = 0;
		virtual bool isFriendly() = 0;
		std::string printContent(std::string="")const;
		std::string getDescription()const;
		Room* getConnectedRoom(int)const;
		bool addDoor(int,Room*);
		bool addReturnDoor(int direction, Room* room);
		bool addItem(std::string);
		bool addActor(Actor*);
		bool removeActor(std::string);
		bool removeItem(std::string);
		bool removeDoor(Room*);
		bool act(Actor* player);
		bool move(Actor*);
		std::vector<std::string>& getItems();
		std::vector<Actor*>& getActors();
		int getNumberOfNPCs()const;
		
		Item* getItem(std::string)const;
		Actor* getActor(std::string)const;
	};
}
#endif
