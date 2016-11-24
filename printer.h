#ifndef JFS_PRINTER_H
#define JFS_PRINTER_H
#include <string>
#include "player.h"
#include "room.h"
namespace labb3 {
	class Printer{
		
		int _numPrintedLines;
		public:
			Printer();
			std::string printScreen(const Player * player, Room * currentRoom);
			void clearScreen();
			std::string printWelcome(const Player * player, Room * currentRoom);
			std::string printCommands();
			std::string printWorld(const Player * player);
			std::string printPickedUpWeapon(Actor * actor, std::string item, std::string oldWeapon);
			std::string printPickedUpItem(Actor * actor, std::string item);
			std::string printCouldNotFindItem(std::string item);
			std::string printDead();
			std::string printGotHit(int damage);
			std::string printCouldNotUnderstandCommand(std::string command);
			std::string printRoomContent(Room * room, std::string command="");
			std::string printSearch(bool isDangerousRoom, Room * room);
			std::string printHit(std::string targetName, Actor * attacker);
			std::string printAttacked(std::string attacker, std::string target, std::string weapon);
			std::string printString(std::string string);
		private: 
			int findNumberOfLines(std::string string)const;
			int getScreenWidth()const;
			int getScreenHeight()const;
	};
	
}

#endif
