#include "item.h"

namespace labb3{
	Item::Item(): _name("Name_Not_Set"), _description("Desc_Not_Set"){
	}
	
	Item::Item(std::string name, std::string desc): _name(name), _description(desc){
	}
	
	Item::Item(std::string name, std::string desc, bool hidden): _name(name), _description(desc), _hidden(hidden){
	
	}
	
	Item::~Item(){
	}
	
	std::string Item::getName()const{
		return _name;
	}
	std::string Item::getDescription()const{
		return _description;
	}
			
	bool Item::getHidden()const{
		return _hidden;
	}
	
	bool Item::setHidden(bool hidden){
		_hidden = hidden;
	}			
	
	
	void Item::setName(std::string name){
		_name = name;
	}
	void Item::setDescription(std::string desc){
		_description = desc;
	}
	
	std::ostream & operator<<(std::ostream & os, Item const& w){
		os<<w._name<<" \tDESCRIPTION: "<<w._description;
		return os;
	}
}
