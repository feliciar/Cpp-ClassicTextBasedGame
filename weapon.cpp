#include "weapon.h"

namespace labb3{

	Weapon::Weapon() : Item("Name_Not_Set","Desc_Not_Set"), _damage(0){
	//_name("Name_Not_Set"), _description("Desc_Not_Set"), _damage(0){
	
	}
	
	Weapon::Weapon(std::string name, std::string desc): Item(name,desc), _damage(0){
	//_name(name), _description(desc), _damage(0){
	
	}
	
	Weapon::Weapon(std::string name, std::string desc, int damage): Item(name,desc), _damage(damage){
	//_name(name), _description(desc), _damage(damage){
	
	}
	
	Weapon::Weapon(std::string name, std::string desc, int damage, bool hidden): Item(name, desc, hidden), _damage(damage){
	//_name(name), _description(desc), _damage(damage),_hidden(hidden){
	
	}
		
	void Weapon::setDamage(int damage){
		_damage = damage;
	}
	int Weapon::getDamage()const{
		return _damage;
	}
	
	std::ostream & operator<<(std::ostream & os, Weapon const& w){
		os<<w._name<<" \tDAMAGE: "<<w._damage<<" \tDESCRIPTION: "<<w._description;
		return os;
	}
}
