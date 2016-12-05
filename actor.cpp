#include "actor.h"
namespace labb3 {

	Actor::~Actor(){
	}
	std::string Actor::getName()const{
		return _name;
	}

	std::string Actor::getDescription()const{
		return _description;
	}

	
	bool Actor::getHidden()const{
		return _hidden;
	}
	void Actor::setName(std::string name){
		_name = name;
	}
	void Actor::setDescription(std::string desc){
		_description = desc;
	}
	void Actor::setHidden(bool hidden){
		_hidden = hidden;
	}
			
	std::ostream & operator<<(std::ostream & os, Actor const& actor){
		os<<actor.getName();
		return os;
	}

}

