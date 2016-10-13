#include "friendly.h"
namespace labb3{


		Friendly::Friendly(std::string name, std::string descript, bool hidden){
			_name = name; 
			_description = descript;
			_hidden = hidden;
		}
		
		Friendly::~Friendly(){
		}
		
		bool Friendly::action(Actor*){
			std::cout<<_description<<std::endl;
		
		}
		
		bool Friendly::move(){
		
		}
	
}
