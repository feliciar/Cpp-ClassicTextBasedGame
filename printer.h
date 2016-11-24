#ifndef JFS_PRINTER_H
#define JFS_PRINTER_H
#include <string>
#include "player.h"
#include "room.h"
namespace labb3 {
	class Printer{
		
		int _numPrintedLines;
		public:
			std::string printScreen(const Player * player, Room * currentRoom);
			void clearScreen();
			std::string printWelcome(const Player * player, Room * currentRoom);
			std::string printCommands();
			std::string printWorld(const Player * player);
			std::string printPickedUpWeapon(Actor * actor, std::string item, std::string oldWeapon);
			std::string printPickedUpItem(Actor * actor, std::string item);
			std::string printCouldNotFindItem(std::string item);
		private: 
			int findNumberOfLines(std::string string)const;
	};
	
}

#endif
