#include "friendlyRoom.h"
#include <iostream>

namespace labb3{
	
	FriendlyRoom::FriendlyRoom(){
		_healingPower = 10;
	}
	
	FriendlyRoom::FriendlyRoom(std::string string){
		_description = string; 
		_healingPower = 10;
	}
	
	FriendlyRoom::~FriendlyRoom(){
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
	
	bool FriendlyRoom::interact(Actor* player){
		Dangerous* d = dynamic_cast<Dangerous*>(player);
		if(d!=nullptr){
			int healthAdded = d->replenishHealth(_healingPower);
			return true;
		}
		return false; 
	}

	bool FriendlyRoom::isFriendly(){
		return true;
	}

}
