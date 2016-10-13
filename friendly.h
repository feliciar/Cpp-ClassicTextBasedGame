#ifndef JFS_FRIENDLY_H
#define JFS_FRIENDLY_H

#include "actor.h"

namespace labb3 {
	class Friendly : public Actor {
		public: 
		Friendly(std::string name, std::string descript, bool hidden=false);
		virtual ~Friendly();
		virtual bool action(Actor*);
		virtual bool move();
	
	};
}
#endif
