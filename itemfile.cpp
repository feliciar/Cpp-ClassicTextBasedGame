#include "itemfile.h"
namespace labb3{

	std::map<std::string, Item*>& ItemFile::getItems(){
		static std::map<std::string, Item*> _items = {
			{"axe",new Weapon("axe", "coolio axio",2)},
			{"teeth",new Weapon("teeth", "sharp poisonous teeth", 10)},
			{"gloves", new Weapon("gloves", "only dainty leather gloves", 1)},
			{"fangs", new Weapon("fangs", "sharp fangs", 3)},
			{"club", new Weapon("club", "heavy club", 3)},
			{"sword", new Weapon("sword", "magical shiny stabby-sword", 10)},
			{"big fangs", new Weapon("big fangs", "big sharp fangs", 5)},
			{"health upgrade", new Item("health upgrade", "upgrades your health by 10")}
		};
		return _items;
	}
	
	ItemFile::~ItemFile(){
		std::map<std::string, Item*> _items=getItems();
		for(auto i:_items){
			delete i.second;
		}
	}
	
}

