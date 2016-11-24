#ifndef JFS_PLAYER_H
#define JFS_PLAYER_H
#include "itemfile.h"
#include "dangerous.h"

namespace labb3 {
	class Player : public Dangerous {
		int _xp = 0; 
		int _xPosition=0;
		int _yPosition=0;
		public:
			Player(int maxLife, std::string _weapon);
			virtual ~Player();
			
			
			virtual bool action(Actor*);
			virtual bool move();
			int getXP()const;
			void setPosition(int x, int y);
			int getXPosition()const;
			int getYPosition()const;
			std::string printPlayerInfo()const;
	};
}

#endif
