#include "game.h"
#include <iostream>
#include <sstream>
/*
#include "item.cpp"
#include "actor.cpp"
#include "room.cpp"
#include "player.cpp"
#include "weapon.cpp"
#include "dangerous.cpp"
#include "friendly.cpp"
*/
namespace labb3{
/*	
	std::map<std::string, Item*> Game::getItems(){
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
*/

	Game::Game(): _player(Player(20, "gloves")){
		
	}
	
	Game::~Game(){

	
		for(Room* room : _rooms){
	
			delete room;
		}
		
		delete _item;
		
	}
	
	bool Game::init(){
		_item = new ItemFile();
		
		//Starting room
		Room* rstart = new FriendlyRoom("You are standing in a dark forest, with a crackling campfire in front of you."); 
		rstart->addActor(&_player);
		_rooms.push_back(rstart);		
		
		Room* r11 = new FriendlyRoom("You are standing on a plateau over a small lake, with a waterfall in front of you.");
		r11->addItem("axe");
		_rooms.push_back(r11);
		
		Room* r12 = new DangerousRoom("Both to the west and south you all you can se is dense forest. ");
		Actor* a12 = new Dangerous("goblin", "Small filthy goblin", 2,"axe");
		r12->addActor(a12);
		_rooms.push_back(r12);
		
		Room* r21 = new DangerousRoom("You are standing on a forest path, water to the east. ");
		Actor* a21 = new Dangerous("small goblin", "Smallish filthy goblin", 2,"axe");
		Actor* a212 = new Dangerous("big goblin", "Smallish filthy goblin", 3,"axe");
		r21->addActor(a21);
		r21->addActor(a212);
		_rooms.push_back(r21);
		
		Room* r22 = new DangerousRoom("");
		Actor* a22 = new Dangerous("goblin", "Distgusting goblin", 5,"axe");
		r22->addActor(a22);
		_rooms.push_back(r22);
		
		Room* r31 = new DangerousRoom("A great stone wall is to the south of you. A cave opening to the north. ");
		Actor* a31 = new Dangerous("puppy", "Dangerous threeheaded puppy", 10,"fangs");
		r31->addActor(a31);
		_rooms.push_back(r31);
		
		Room* r32 = new DangerousRoom();
		_rooms.push_back(r32);
		
		Room* r33 = new DangerousRoom();
		Actor* a33 = new Dangerous("troll", "troooollololo lo lolo lo lolo lo", 4,"club");
		Actor* a332 = new Dangerous("goblin", "Distgusting goblin", 5,"axe");
		r33->addActor(a33);
		r33->addActor(a332);
		_rooms.push_back(r33);
		
		Room* r41 = new DangerousRoom();
		r41->addItem("sword");
		Actor* a41 = new Dangerous("minotaur", "a bull with the head of a man", 30,"club");
		r41->addActor(a41);
		_rooms.push_back(r41);
		
		Room* r51 = new DangerousRoom("You are in a big dark cave. ");
		Actor* a51 = new Dangerous("cave troll", "don't feed the troll", 30,"club");
		r51->addActor(a51);
		_rooms.push_back(r51);
		
		Room* r52 = new DangerousRoom("There is a cave opening to the east of you. ");
		_rooms.push_back(r52);
		
		Room* r53 = new FriendlyRoom();
		Actor* a53 = new Friendly("wood elf", "'Some way along the path there is a mighty dragon! Come prepared if you want to live. ' says the wood elf");
		r53->addActor(a53);
		_rooms.push_back(r53);
		
		Room* r61 = new DangerousRoom();
		Actor* a61 = new Dangerous("cerebous", "Like the puppy, but you know... bigger", 40,"big fangs");
		r61->addActor(a61);
		_rooms.push_back(r61);
		
		Room* r62 = new DangerousRoom();
		r62->addItem("health upgrade");
		_rooms.push_back(r62);
		
		Room* r71 = new DangerousRoom("You are on a narrow stony path, with fire in the forest on both sides of you. ");
		_rooms.push_back(r71);
		
		Room* rend = new DangerousRoom("There's hot boiling lava in front of you, crackling fire on your sides. ");
		Actor* aend = new Dangerous("dragon","dangerous fire-breathing dragon",100,"teeth");
		rend->addActor(aend);
		_rooms.push_back(rend);
		
		//Adding doors
		rstart->addDoor(1, r11);
		rstart->addDoor(3, r12);
		rstart->addDoor(0, r21);
		
		r12->addDoor(0, r22);
		
		r21->addDoor(3, r22);
		r21->addDoor(0, r33);
		r31->addDoor(0, r51);
		r31->addDoor(3, r32);
		
		r32->addDoor(0, r41);
		
		r32->addDoor(3, r33);
		
		r33->addDoor(0, r62);
		
		r41->addDoor(0, r52);
		
		r51->addDoor(3, r52);
		r52->addDoor(3, r53);
		r53->addDoor(0, r61);
		r61->addDoor(3, r62);
		r61->addDoor(0, r71);
		r71->addDoor(0, rend);
		
		_disapearingDoor.first = r61; 
		_disapearingDoor.second = r71; 

		
		_currentRoom = rstart;
		
	}

	bool Game::update(){
		int startHealth = _player.getLife(); 
		
		//_currentRoom->act(_player);
		std::vector<Actor*> actors = _currentRoom->getActors();
		for(int i=0; i<actors.size(); ++i){
			Dangerous* d = dynamic_cast<Dangerous*>(actors[i]);
			if(actors[i]->getName().compare("player")!=0 && d!=nullptr){
				actRandom(actors[i]);
				actors = _currentRoom->getActors();
			}
		}
		
		
		int endHealth = _player.getLife();
		if(endHealth<=0){
			std::cout<<"You died! \nThe next thing you remember is waking up at the ground next to the campfire. "<<std::endl;
			_currentRoom->move(&_player);
			_currentRoom = _rooms[0];
			_currentRoom->addActor(&_player);
			std::cout<<_player<<std::endl;
			std::cout<<_currentRoom->printContent()<<std::endl;
		}
		else if(endHealth<startHealth){
			std::cout<<"You got hit! You lost "<<startHealth-endHealth<<" life. Your current life is "<<endHealth<<std::endl;
		}
		
	}
	
	std::string Game::readCommand()const{
		std::cout<<"Command: ";
		std::string command; 
		getline (std::cin, command);
		//Remove spaces in the end of the submit
		if(command.size()>0){
			if(command.substr(command.size()-1).compare(" ")==0){
				command = command.substr(0, command.size()-1);
			}
		}
		return command;   
	}
	
	bool Game::performCommand(std::string command, Actor* actor){
		std::string originalCommand = command;
		std::vector<std::string> words; 
		//Find first blank
		int spacePos = command.find(" ");
		//Whilst we still have blanks, put all words in array 
		while(spacePos!=-1){
			words.push_back(command.substr(0,spacePos));
			command = command.substr(spacePos+1);
			spacePos = command.find(" ");
		}
		words.push_back(command);
		
		
		if(commandMatches(words, {"pick", "up"}, 3)){
			pickUp(appendSubArrayToString(words,2),actor);
		}else if(commandMatches(words, {"search"}, 1)){
			search();
		}else if(commandMatches(words, {"take"}, 2)){
			pickUp(appendSubArrayToString(words,1),actor);
		}else if(commandMatches(words, {"go"}, 2)){
			go(appendSubArrayToString(words,1),actor);
		}else if(commandMatches(words, {"hit"}, 2)){
			hit(appendSubArrayToString(words,1),actor);
		}else if(commandMatches(words, {"look", "at"}, 3)){
			lookAt(appendSubArrayToString(words,2));
		}else if(commandMatches(words, {"sleep"}, 1)){
			sleep(appendSubArrayToString(words,1));
		}else if(commandMatches(words, {"talk", "to"}, 3)){
			talkTo(appendSubArrayToString(words,2), actor);
		}else if(commandMatches(words, {"help"},1) || commandMatches(words, {"h"},1) || commandMatches(words, {"?"},1)){
			std::cout<<"The available commands are: "<<std::endl;
			std::cout<<printCommands()<<std::endl;
		}else {
			std::cout<<"did not understand command "<<originalCommand<<std::endl;
			return false;
		}
	
		
		
	}
	/*
	 * Check if the command words matches our words, and if it has at least the right size. 
	 * @param words the input words
	 * @param commandToMatch, for example "pick up"
	 * @param wordCount, the minimum count of words wanted in words, for example 3 for "pick up [item]"
	 *
	 */
	bool Game::commandMatches(std::vector<std::string> words, std::vector<std::string> commandToMatch, int wordCount)const{
		if(words.size()>=wordCount){
			for(int i=0; i<commandToMatch.size(); ++i){
				if(words[i].compare(commandToMatch[i])!=0) 
					return false; 
			}
			return true;
		}		
		 return false;
	}
	
	/*
	 * @param Array to put into string
	 * @param position, concatinate all words after (and including) this position. (number of words we want to remove)
	 */
	std::string Game::appendSubArrayToString(std::vector<std::string> array, int position)const{
		std::string result = ""; 
		for(int i=position; i<array.size(); ++i){
			result.append(array[i]);
			if(i!=array.size()-1)
				result.append(" ");
		}
		return result; 
	}
	
	bool Game::pickUp(std::string item, Actor* actor){
		if(ItemFile::getItems().find(item)!=ItemFile::getItems().end()){
			Item* i = ItemFile::getItems().find(item)->second; 
			Dangerous* d = dynamic_cast<Dangerous*>(actor);
			
			Weapon* w = dynamic_cast<Weapon*>(i);
			if(w!=nullptr && d!= nullptr){
				
				_currentRoom->removeItem(item);
				std::string oldWeapon = d->changeWeapon(item);
				_currentRoom->addItem(oldWeapon);
				if(actor->getName().compare("player")==0){
					std::cout<<"You picked up "<<item<<" and left behind your old "<<oldWeapon<<std::endl;
				} else {
					std::cout<<actor->getName()<<" picked up "<<item<<" and left behind it's old "<<oldWeapon<<std::endl;
				}
			}else if(w==nullptr && d!= nullptr){
				d->healthUpgradeItem(item);
				_currentRoom->removeItem(item);
				if(actor->getName().compare("player")==0){
					std::cout<<"You picked up "<<item<<" and increased your max health by 10"<<std::endl;
				} else {
					std::cout<<actor->getName()<<" picked up " <<item<<std::endl;
					
				}
			}
			return true;
		}else {
			std::cout<<"Could not find item "<<item<<std::endl;
			return false;
		}
	}
	
	bool Game::search(){
		std::cout<<_currentRoom->printContent("search")<<std::endl;
		
		DangerousRoom *d = dynamic_cast<DangerousRoom*>(_currentRoom);
		if(d!=nullptr){
			int damage = d->getDamage();
			std::cout<<"You take damage from the dangerous spiders and rats lurking in the shadows. "<<std::endl;
			_player.getHit(damage);
		}
	}
	
	bool Game::go(std::string direction, Actor* actor){
		Room* next = nullptr; 
		if(direction.compare("north")==0||direction.compare("n")==0){
			next = _currentRoom->getConnectedRoom(0); 
		}else if(direction.compare("west")==0||direction.compare("w")==0){
			next = _currentRoom->getConnectedRoom(3);
		}else if(direction.compare("south")==0||direction.compare("s")==0){
			next = _currentRoom->getConnectedRoom(2);
		}else if(direction.compare("east")==0||direction.compare("e")==0){
			next = _currentRoom->getConnectedRoom(1);
		}
		if(next!=nullptr){
			actor->move();
			if(_currentRoom->move(actor)){
				next->addActor(actor);
			}else{
				return false;
			}
			
			if(actor->getName().compare("player")==0){
				if(next==_disapearingDoor.second && _currentRoom==_disapearingDoor.first){
					next->removeDoor(_currentRoom);
					std::cout<<"You fell down a hole, and you can't get back up. "<<std::endl;
				}
				_currentRoom = next; 
				Player* p = dynamic_cast<Player*>(actor);
				std::cout<<*p<<std::endl;
				std::cout<<_currentRoom->printContent();
			} else {
				std::cout<<actor->getName()<<" left the area."<<std::endl;
			}
			return true;
		}else {
			if(actor->getName().compare("player")==0)
				std::cout<<"No door here"<<std::endl;
			return false;	
		}
	}
	
	bool Game::hit(std::string acton, Actor* actoff){
		
		Dangerous* d = dynamic_cast<Dangerous*>(actoff);
		Player* p = dynamic_cast<Player*>(actoff);
		Actor* a = _currentRoom->getActor(acton);
		if(a!=nullptr){
			Dangerous* dan = dynamic_cast<Dangerous*>(a);
			//Player* pan = dynamic_cast<Player*>(a);
			if(dan!=nullptr){
				if(actoff->getName().compare("player")==0)
					std::cout<<"You attacked "<<acton<<" with your "<<d->getWeapon()<<std::endl;
				if(actoff->getName().compare("player")!=0&&acton.compare("player")!=0)
					std::cout<<actoff->getName()<<" attacked "<<acton<<" with "<<d->getWeapon()<<std::endl;
				d->action(dan);
				if(dan->getLife()==0){
					if(acton.compare("player")!=0){
						std::cout<<acton<<" died. Good job! He dropped his weapon. "<<std::endl;
						_currentRoom->addItem(dan->getWeapon()); 
						_currentRoom->removeActor(acton);
					}else{
						
					}
					if(acton.compare("dragon")==0){
						win = true; 
						return true;
					}
					if(actoff->getName().compare("player")==0)
						std::cout<<"your new life: "<<d->getLife()<<" xp: "<<p->getXP()<<std::endl;
				}else{
					if(acton.compare("player")!=0)
						std::cout<<acton<<"'s new life is "<<dan->getLife()<<std::endl; 
				}
				return true;
			}else{
				if(actoff->getName().compare("player")==0)
					std::cout<<"Could not attack "<<acton<<". It is friendly"<<std::endl;
				return false;
			}
		}else  {
			if(actoff->getName().compare("player")==0)
				std::cout<<"Could not find "<<acton<<" to attack"<<std::endl;
			return false;
		}
		
		
	}
	
	bool Game::lookAt(std::string item)const{
		Item* i = _currentRoom->getItem(item);
		Weapon* w = dynamic_cast<Weapon*>(i);
		Actor* a = _currentRoom->getActor(item);
		if(i!=nullptr){
			std::stringstream descStream;
			if(w!=nullptr){
				descStream<<*w<<std::endl;
			}else {
				descStream<<*i<<std::endl;
			}
			std::cout<<descStream.str()<<std::endl;
		}else if(a!=nullptr){
			std::cout<<a->getDescription()<<std::endl;
		}else {
			std::cout<<"Could not find "<<item<<std::endl;
		}
		
	}
	
	bool Game::sleep(std::string stuff){
		_currentRoom->interact(&_player);
	}
	
	bool Game::talkTo(std::string text, Actor* actor){
		Actor* a = _currentRoom->getActor(text);
		Friendly* f = dynamic_cast<Friendly*>(a);
		if(f!=nullptr){
			f->action(actor);
		} else if(a!=nullptr) {
			std::cout<<"Can't talk to "<<text<<"."<<std::endl;
		} else {
			std::cout<<"Can't find a "<<text<<" to talk to."<<std::endl;	
		}
	}
	
	
	void Game::actRandom(Actor* actor){
		int random = rand()% 8; //between 0 and 9
		
		while(random==0 && _currentRoom->getItems().size()==0){ //Could not pick up item. Randomize again
			random = rand()%8;
		}
		switch(random){
			case 0 : {
				std::string command = ""; 
				command = "pick up "; 
				int randItem = rand()%_currentRoom->getItems().size();
				command.append(_currentRoom->getItems()[randItem]);
				performCommand(command, actor);
				break;
				}
			case 1 : {
				std::string command = "";
				bool foundDir = false;
				while(!foundDir){
					int randDirection = rand()%4; 
					switch(randDirection){
						case 0 : command = "go north";
						break; 
						case 1 : command = "go east";
						break; 
						case 2 : command = "go south";
						break; 
						case 3 : command = "go west";
						break;
					}
					foundDir = performCommand(command, actor);
				}
				break;
				}
			default : {//The change of hit is 
				std::string command = "";
				command = "hit ";
				
				if(_currentRoom->getActors().size()==2){
					command.append("player");
					performCommand(command, actor);
					return; 
				}
				
				bool finished = false;
				for(int i=0; i<3; ++i){ //Gets three shots to hit a correct actor
					if(!finished){
						int randActor = rand()%_currentRoom->getActors().size();
						Actor* other = _currentRoom->getActors()[randActor];
						if(other->getName().compare(actor->getName())!=0){
							command.append(other->getName());
							finished = performCommand(command, actor);
						}
					
					}
				}
				
		
				
				break;
			}
	
		}
	
	
	}

	Player* Game::getPlayer(){
		return &_player;

	}
	
	std::string Game::printWelcome()const{
		std::string string = "";
		std::stringstream descStream;
		descStream<<_player<<std::endl;
		string.append(descStream.str());
		string.append("\nWelcome! \n");
		string.append("With no recollection of where you are or who you are,\n");
		string.append("you hear a distant roar to the north. \n");
		
		
		
		string.append("If you are confused just say 'help', or try to go somewhere. \n");
		string.append(_currentRoom->printContent());
		return string;
	}
	
	std::string Game::printCommands()const{
		std::string printString =  "go [direction]\t to go somewhere\n";
		printString.append("hit [enemy]\t to attack something\n");
		printString.append("pick up [item]\t to pick something up\n");
		printString.append("look at [thing]\t to look closer at something, to find out more\n");
		printString.append("talk to [friend] to talk to someone\n");
		printString.append("search\t\t to see what is around you\n");
		printString.append("sleep\t\t to rest and regain some health");
		return printString;
		
		
	}
   
}


int main(){
		
		labb3::Game game; 
		game.init();
		std::cout<<"###-------------###-------------###---------------------------------------------"<<std::endl;
		std::cout<<game.printWelcome();
		std::string command = ""; 
		command = game.readCommand();
		while(command.compare("exit")!=0 && !game.win){
			std::cout<<"###-------------###-------------###---------------------------------------------"<<std::endl;
			if(game.performCommand(command, game.getPlayer()) && command.substr(0, 2).compare("go")!=0){
				game.update();
			}
			if(game.win) break;
			command = game.readCommand();
		}
		if(game.win){
			std::cout<<"You are the coolest! You defeated the great dragon. You are winner!!! "<<std::endl;
		}
		std::cout<<"Bye bye!"<<std::endl;
}
	
