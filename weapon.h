#ifndef JFS_WEAPON_H
#define JFS_WEAPON_H
#include "item.h"
namespace labb3{
	class Weapon : public Item{
		int _damage;
	public:
		Weapon();
		Weapon(std::string name, std::string desc);
		Weapon(std::string name, std::string desc, int damage);
		Weapon(std::string name, std::string desc, int damage, bool hidden);
		
		void setDamage(int damage);
		int getDamage()const;
		friend std::ostream & operator<<(std::ostream & os, Weapon const &);
	};
	
	std::ostream & operator<<(std::ostream & os, Weapon const &);
}
#endif
