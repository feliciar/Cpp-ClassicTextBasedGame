#ifndef JFS_PLAYER_H
#define JFS_PLAYER_H
#include "itemfile.h"
#include "dangerous.h"

namespace labb3 {
	class Player : public Dangerous {
		int _xp = 0; 
		public:
			Player(int maxLife, std::string _weapon);
			virtual ~Player();
			
			
			virtual bool action(Actor*);
			virtual bool move();
			int getXP()const;
	};
	std::ostream & operator<<(std::ostream & os, Player const &);
}

#endif
