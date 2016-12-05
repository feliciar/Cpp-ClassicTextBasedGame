#include <iostream>
#include "dangerousRoom.h"

namespace labb3{
	
	DangerousRoom::DangerousRoom(){
		_damage = 1;
	}
	
	DangerousRoom::DangerousRoom(std::string string){
		_description = string; 
		_damage = 1;
	}

	DangerousRoom::~DangerousRoom(){
		for(int i = 0;i<_actors.size();++i){
			if(_actors[i]!=nullptr){
				if(_actors[i]->getName().compare("player")!=0){
					delete _actors[i];
					_actors[i] =nullptr;
				}
			}
			/*
			Dangerous* d = nullptr;
			Player* p = nullptr;
			Friendly* f = nullptr;
			d = dynamic_cast<Dangerous*>(_actors[i]);
			p = dynamic_cast<Player*>(_actors[i]);
			f = dynamic_cast<Friendly*> (_actors[i]);
			if(d!=nullptr && p==nullptr){
				delete d;
			} else if(d==nullptr && p==nullptr && f!=nullptr) {
				delete f;
			}
			_actors[i]=nullptr;
			*/
		}	
	}
	
	bool DangerousRoom::interact(Actor* _player){
		return true;
	}
	
	int DangerousRoom::getDamage()const{
		return _damage;
	}

	bool DangerousRoom::isFriendly(){
		return false;
	}


}
