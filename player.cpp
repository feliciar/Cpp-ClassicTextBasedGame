
#include "player.h"
 #include <typeinfo> 
namespace labb3 {
	Player::Player(int maxLife, std::string weapon) : Dangerous(maxLife, weapon){	
		_name = "player";
	}
	
	Player::~Player(){
	}
	

	
	
	
	bool Player::action(Actor* other){
		Dangerous* dan = dynamic_cast<Dangerous*>(other);
		if(dan!=nullptr){
			Item* w = ItemFile::getItems().find(_weapon)->second;
			if(typeid(*w)==typeid(Weapon)){
				Weapon* wep = dynamic_cast<Weapon*>(w);
				if(wep!=nullptr){
					int lifeLeft = dan->getHit(wep->getDamage()+getXP());
					if(lifeLeft==0)
						++_xp;
					return true;
				}
			}
		}
		return false;
	}
	
	bool Player::move(){
		if(_life+1<=_maxLife){
			_life+=1;
			std::cout<<"Replenished some of your health"<<std::endl;
		}		
	}
	
	int Player::getXP()const{
		return _xp; 
	}
	
	std::ostream & operator<<(std::ostream & os, Player const& p){
		Weapon* wep = dynamic_cast<Weapon*>(ItemFile::getItems().find(p.getWeapon())->second);
		os<<"LIFE: "<<p.getLife()<<" \tMAX LIFE: "<<p.getMaxHealth()<<" \tXP: "<<p.getXP()<<" \nWEAPON: "<<*wep;
		return os;
	}
	
}

