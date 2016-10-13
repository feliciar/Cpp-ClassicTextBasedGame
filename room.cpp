#include "room.h"
namespace labb3{
	Room::Room(){
		
		std::vector<Room*> d(4);
		_doors = d;
	}
	
	Room::Room(std::string d) : _description(d){
		std::vector<Room*> room(4);
		_doors = room;
	}
	
	Room::~Room(){
		for(int i = 0;i<_actors.size();++i){
			
			if(_actors[i]!=nullptr){
				if(_actors[i]->getName().compare("player")!=0){
					delete _actors[i];
					_actors[i] =nullptr;
				}
			}
		}
	}
	
	/*
	 *@param string command, if is search print hidden
	 */
	std::string Room::printContent(std::string command)const{
		std::stringstream descStream;
		descStream<<_description<<std::endl;
		bool seeHidden = false;
		if(command.compare("search")==0){
			seeHidden = true;
		}
		int numNPCs = getNumberOfNPCs();
		if(seeHidden){
			
			if(numNPCs>=1){
				descStream<<"You see ";
			}
			int i=0;
			for(;i<(int)(numNPCs-1) ;++i){
				descStream<<"a "<<*_actors[i]<<","<<std::endl;
			}
			if(numNPCs>1){
				descStream<<"and ";
			}
			if(numNPCs>=1){
				descStream<<"a "<<*_actors[numNPCs-1]<<"."<<std::endl;
			}
			if(_items.size()>=1){
				descStream<<"You see ";
			}
			i=0;
			for(;i<(int)(_items.size()-1);++i){
				descStream<<"a "<<_items[i]<<","<<std::endl;
			}
			if(_items.size()>1){
				descStream<<"and ";
			}
			if(_items.size()>=1){
				descStream<<"a "<<_items[_items.size()-1]<<"."<<std::endl;
			}

		} else {
			bool notHidden = false;
			bool mulNotHidden = false;
			int lastNotHidden = 0;
			int i = 0;
			for(int j = 0; j<numNPCs; ++j){
				if(!_actors[j]->getHidden()){					
					if(notHidden){
						mulNotHidden = true;
					}
					notHidden = true;
					lastNotHidden = i;
				}
				++i;
			}
			if(numNPCs>=1 && notHidden){
				descStream<<"You see ";
			}
			i=0;
			for(;i<(lastNotHidden);++i){
				if(!_actors[i]->getHidden()){
					
					descStream<<"a "<<*_actors[i]<<","<<std::endl;
				}
			}
			if(numNPCs>1 && mulNotHidden){
				descStream<<"and ";
			}
			if(numNPCs>=1 && notHidden){
				descStream<<"a "<<*_actors[lastNotHidden]<<"."<<std::endl;
			}
			
			notHidden = false;
			lastNotHidden = 0;
			i=0;
			std::map<std::string, Item*> tmp = ItemFile::getItems();
						
			for(;i<_items.size();++i){
				if(!(tmp.find(_items[i])->second->getHidden())){
					if(notHidden){
						mulNotHidden = true;
					}
					notHidden = true;
					lastNotHidden = i;
				}
			}
						
			if(_items.size()>=1 && notHidden){
				descStream<<"You see ";
			}
			i=0;
			for(;i<(int)(lastNotHidden);++i){
				if(!(tmp.find(_items[i])->second->getHidden())){
					descStream<<"a "<<_items[i]<<","<<std::endl;
				}
			}
			if(_items.size()>1 && mulNotHidden){
				descStream<<"and ";
			}
			if(_items.size()>=1 && notHidden){
				descStream<<"a "<<_items[lastNotHidden]<<"."<<std::endl;
			}
			
		}
		if(_doors[0]!=nullptr)
			descStream<<"Door To The North"<<std::endl;
		if(_doors[1]!=nullptr)
			descStream<<"Door To The East"<<std::endl;
		if(_doors[2]!=nullptr)
			descStream<<"Door To The South"<<std::endl;
		if(_doors[3]!=nullptr)
			descStream<<"Door To The West"<<std::endl;
				
		return descStream.str();
	}
	
	std::string Room::getDescription()const{
		return _description;
	}
	
	Room* Room::getConnectedRoom(int direction)const{
		return _doors[direction];
	}
	
	bool Room::addDoor(int direction , Room* room){
		_doors[direction] = room;
		int otherDir = (direction+2)%4;
		
		/*
		switch(direction){
			case 0 : 
				otherDir=2; 
				break;
			case 1 : 
				otherDir = 3; 
				break; 
			case 2 : 
				otherDir = 0; 
				break;
			case 3 : 
				otherDir = 1; 
		}
		*/
		room->addReturnDoor(otherDir, this);
	}
	
	bool Room::addReturnDoor(int direction, Room* room){
		_doors[direction] = room;
	}
	
	bool Room::addItem(std::string item){
		_items.push_back(item);
	}
	
	bool Room::addActor(Actor* actor){
		_actors.push_back(actor);
	}
	
	bool Room::removeActor(std::string name){
		for(int i = 0; i < _actors.size(); ++i){
			if(_actors[i]->getName().compare(name)==0){

					delete _actors[i];
				
				_actors.erase(_actors.begin()+i);
				return true;
			}
		}
		return false;
	}
	
	bool Room::move(Actor* actor){
		for(int i =0 ;i<_actors.size();++i){
			if(actor==_actors[i]){
				_actors.erase(_actors.begin()+i);
				return true;
			}
		}
		return false;
	}
	
	bool Room::removeItem(std::string name){
		for(int i = 0; i < _items.size(); ++i){
			if(_items[i].compare(name)==0){
				_items.erase(_items.begin()+i);
				return true;
			}
		}
		return false;
	}
	
	bool Room::removeDoor(Room* room){
		
		for(int i=0; i<_doors.size(); ++i){
			if(room==_doors[i]){
				_doors[i] = nullptr;
				return true;
			}
		}	
		return false;
	}
	
	bool Room::act(Actor* player){
		for(auto actor: _actors){
			actor->action(player);
		}
	}
	
	std::vector<std::string>& Room::getItems(){
		return _items; 
	}
	
	std::vector<Actor*>& Room::getActors(){
		return _actors; 
	}
	
	int Room::getNumberOfNPCs()const{
		Player* p = dynamic_cast<Player*>(_actors[_actors.size()-1]);
		if(p!=nullptr){
			return _actors.size()-1;
		}else{
			return _actors.size();
		}
	}
	
	Item* Room::getItem(std::string item)const{
		for(auto i:_items){
			if(i.compare(item)==0){
				std::map<std::string, Item*> tmp = ItemFile::getItems();
				return tmp.find(item)->second;
			}
		}
		return nullptr;	
	}
	
	
	Actor* Room::getActor(std::string actor)const{
		for(auto a:_actors){
			if(a->getName().compare(actor)==0){
				return a;
			}
		}
		return nullptr;
	}
}
