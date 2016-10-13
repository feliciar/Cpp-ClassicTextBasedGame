#ifndef JFS_DANGEROUS_H
#define JFS_DANGEROUS_H
#include "itemfile.h"
#include "actor.h"
#include "weapon.h"

namespace labb3 {
	class Dangerous : public Actor {
		protected: 
			std::string _weapon;	
			int _life;
			int _maxLife;
		public:
			Dangerous(int maxLife, std::string _weapon);
			Dangerous(std::string name, std::string descript, int maxLife, std::string weapon);
			virtual ~Dangerous();
			/* 
			 * @param Damage dealt to this actor
			 * @return life left
			 */
			int getHit(int);
			/*
			 * Resets this dangerous's health
			 */
			void replenishHealth();
			int replenishHealth(int);
			
			int setMaxHealth(int);
			int getMaxHealth()const;
			int healthUpgradeItem(std::string);
			std::string changeWeapon(std::string);
			virtual bool action(Actor*);
			virtual bool move();
			
			int getLife()const;
			
			std::string getWeapon()const;
	};
}

#endif
