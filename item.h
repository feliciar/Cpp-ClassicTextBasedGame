#ifndef JFS_ITEM_H
#define JFS_ITEM_H
#include <iostream>

namespace labb3{
	class Item{
		protected: 	
			bool _hidden = false;
			std::string _name;
			std::string _description;
		
		public:
			Item();
			Item(std::string name, std::string desc);
			Item(std::string name, std::string desc, bool);
			~Item();
			
			virtual std::string getName()const;
			std::string getDescription()const;
			bool getHidden()const;
			
			bool setHidden(bool);
			void setName(std::string);
			void setDescription(std::string);
			friend std::ostream & operator<<(std::ostream & os, Item const &);
	};
	std::ostream & operator<<(std::ostream & os, Item const &);

}
#endif
