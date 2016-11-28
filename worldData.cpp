#include "worldData.h"

namespace labb3{


	Room* WorldData::initWorld(std::vector<Room*> * _rooms, Player * _player, std::pair<Room*, Room*>* _disapearingDoor){
		Room* startRoom = new FriendlyRoom("You are standing in a dark forest, you see a light to the north. "); 
		_rooms->push_back(startRoom);		

		Room* campfire = new FriendlyRoom("You have a crackling campfire in front of you. You feel safe here."); 
		_rooms->push_back(campfire);		
		
		Room* plateau = new FriendlyRoom("You are standing on a plateau over a lake. You have a waterfall in front of you, and a forrest to the south.");
		plateau->addItem("tooth brush");
		_rooms->push_back(plateau);
		
		Room* lakeShore = new DangerousRoom("You are standing on the lake shore. ");
		Actor* a12 = new Dangerous("goblin", "Small filthy goblin", 2,"axe");
		lakeShore->addActor(a12);
		_rooms->push_back(lakeShore);
		
		Room* doubleGoblin = new DangerousRoom("A mountain rises right to the east, and the dense forrest is to the south. ");
		Actor* a21 = new Dangerous("small goblin", "Smallish filthy goblin", 2,"axe");
		Actor* a212 = new Dangerous("big goblin", "Smallish filthy goblin", 3,"axe");
		doubleGoblin->addActor(a21);
		doubleGoblin->addActor(a212);
		_rooms->push_back(doubleGoblin);
		
		Room* r22 = new DangerousRoom("You have water to the west, and a great stone wall rises to the east. You see a cave opening in the mountain. ");
		Actor* a22 = new Dangerous("goblin", "Distgusting goblin", 5,"axe");
		r22->addActor(a22);
		_rooms->push_back(r22);
		
		Room* r31 = new DangerousRoom("You are in a musky cave. The light is dim. ");
		Actor* a31 = new Dangerous("puppy", "Dangerous threeheaded puppy", 10,"fangs");
		r31->addActor(a31);
		_rooms->push_back(r31);
		
		Room* r32 = new DangerousRoom();
		_rooms->push_back(r32);
		
		Room* r33 = new DangerousRoom("You see great rocks. There is a small clift in the stone wall to the west. Maybe you can get through there...");
		Actor* a33 = new Dangerous("troll", "troooollololo lo lolo lo lolo lo", 4,"club");
		Actor* a332 = new Dangerous("goblin", "Distgusting goblin", 5,"axe");
		r33->addActor(a33);
		r33->addActor(a332);
		_rooms->push_back(r33);

		Room* narrowPath = new DangerousRoom();
		_rooms->push_back(narrowPath);
		
		Room* r41 = new DangerousRoom();
		r41->addItem("sword");
		Actor* a41 = new Dangerous("minotaur", "a bull with the head of a man", 30,"club");
		r41->addActor(a41);
		_rooms->push_back(r41);
		
		Room* r53 = new FriendlyRoom();
		Actor* a53 = new Friendly("wood elf", "'Some way along the path there is a mighty dragon! Come prepared if you want to live. ' says the wood elf");
		r53->addActor(a53);
		_rooms->push_back(r53);

		Room* healthRoom = new FriendlyRoom();
		healthRoom->addItem("health upgrade");
		_rooms->push_back(healthRoom);
		
		Room* r62 = new DangerousRoom();
		_rooms->push_back(r62);
		
		Room* r71 = new DangerousRoom("You are on a narrow stony path, with fire in the forest on both sides of you. ");
		_rooms->push_back(r71);
		
		Room* rend = new DangerousRoom("There's hot boiling lava in front of you, crackling fire on your sides. ");
		Actor* aend = new Dangerous("dragon","dangerous fire-breathing dragon",100,"teeth");
		rend->addActor(aend);
		_rooms->push_back(rend);
		

		/*
		       ________
		 _____|8 === 8 |_
		|8  8  8 ~~~ 8  8|   
		|8  8 ~~~ 8  8 |||
		~~~~~~ 8  8  8 |
		      444 8 444
		      444444444


		       ________
		 _____|  ===   |_
		|        ~~~     |   
		|     ~~~      |||
		~~~~~~         |
		      444   444
		      444444444

		*/

		//Adding doors
		startRoom->addDoor(0, campfire);

		campfire->addDoor(3, plateau);
		campfire->addDoor(0, lakeShore);
		campfire->addDoor(1, doubleGoblin);
		
		lakeShore->addDoor(1, r32);
		
		doubleGoblin->addDoor(0, r32);
		
		r32->addDoor(0, r22);
		
		r22->addDoor(0, r33);
		r22->addDoor(1, r31);
		
		r33->addDoor(3, narrowPath);
		narrowPath->addDoor(3, r41);
		
		r41->addDoor(2, r53);
		
		r53->addDoor(3, r62);

		r62->addDoor(2, r71);
		r62->addDoor(3,healthRoom);

		r71->addDoor(3, rend);
		
		_disapearingDoor->first = r62; 
		_disapearingDoor->second = r71; 

		
		
		//_currentRoom = r71;
		startRoom->addActor(_player);
		//_currentRoom->addActor(&_player);
		_player->setPosition(3,4);
		return startRoom;
	}
}