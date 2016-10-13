#include "dangerous.h"
#include <typeinfo> 
namespace labb3 {

	Dangerous::Dangerous(int maxLife, std::string weapon) : _maxLife(maxLife), _weapon(weapon), _life(maxLife){
	}
	
	Dangerous::Dangerous(std::string name, std::string description, int maxLife, std::string weapon) :  _maxLife(maxLife), _weapon(weapon), _life(maxLife){
		_name = name;
		_description = description;
	}
	
	Dangerous::~Dangerous(){
	}
	
	/* 
	 * This dangerous gets hit by other actor
	 * @param Damage dealt to this actor
	 * @return life left
	 */
	int Dangerous::getHit(int damageDealt){
		_life-=damageDealt; 
		if(_life<0) _life=0; 
		return _life; 
	}
	
	/*
	 * Resets this dangerous's health
	 */
	void Dangerous::replenishHealth(){
		_life = _maxLife; 
	
	}
	
	/*
	 * Increases this dangerous's health with specified health to add. Returns new health
	 */
	int Dangerous::replenishHealth(int healthToAdd){
		if(_life+healthToAdd>_maxLife)
			_life = _maxLife; 
		else 
			_life+=healthToAdd;
		return _life;
	
	}
	
	/*
	 * sets maxhealth and return new health
	 */
	int Dangerous::setMaxHealth(int newMax){
		_maxLife = newMax;
		return _maxLife;
	}
	
	int Dangerous::getMaxHealth()const{
		return _maxLife;
	}
	
	int Dangerous::healthUpgradeItem(std::string item){
		if(item.compare("health upgrade")==0){
			_life+=10; 
			return setMaxHealth(getMaxHealth()+10);
		}
		return getMaxHealth();	
	}
	
	std::string Dangerous::changeWeapon(std::string newWeapon){
		std::string tmp = _weapon;
		_weapon = newWeapon; 
		return tmp;
	}
	
	/*
	 * Perform action hit on other actor
	 */
	bool Dangerous::action(Actor* other){
		Dangerous* dan = dynamic_cast<Dangerous*>(other);
		if(dan!=nullptr){
			//Don't hit if your health is too low
			if(_life<=(int)(_maxLife*0.2)){
				return false; 
			}else{
				Item* w = ItemFile::getItems().find(_weapon)->second;
				if(typeid(*w)==typeid(Weapon)){
					Weapon* wep = dynamic_cast<Weapon*>(w);
					if(wep!=nullptr){
						int damage = rand()%wep->getDamage()+1;
						dan->getHit(damage);
						return true;
					}
				}
			}
		}
		return false;
	}
	
	bool Dangerous::move(){
	
	
	}
	
	int Dangerous::getLife()const{
		return _life;
	}

	std::string Dangerous::getWeapon()const{
		return _weapon;
	}
}


