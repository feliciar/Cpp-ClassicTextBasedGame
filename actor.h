#ifndef JFS_ACTOR_H
#define JFS_ACTOR_H

#include <iostream>
namespace labb3 {
	class Actor{
		protected: 
			bool _hidden = false;
			std::string _name ="";
			std::string _description="";		
		
		public:
			virtual ~Actor();
			virtual bool action(Actor* other) = 0;
			virtual bool move() = 0;
			std::string getName()const;
			std::string getDescription()const;
			bool getHidden()const;
			
			void setName(std::string name);
			void setDescription(std::string desc);
			void setHidden(bool hidden);
			virtual bool isFriendly() = 0; 

	};
	
	std::ostream & operator<<(std::ostream & os, Actor const &);
}

#endif
