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

	Game::Game(): _player(Player(20, "gloves")){
		
	}
	
	Game::~Game(){

	
		for(Room* room : _rooms){
	
			delete room;
		}
		
		delete _item;
		delete _printer;
		
	}
	
	bool Game::init(){

		_printer = new Printer();

		_item = new ItemFile();
		
		WorldData* w = new WorldData();
		_currentRoom = w->initWorld(&_rooms, &_player, &_disapearingDoor);

		delete w;
		
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
			handleDeath();
		}
		else if(endHealth<startHealth){
			_eventDescriptions.append(_printer->printGotHit(startHealth-endHealth));
		}
		
	}

	void Game::handleDeath(){
		_currentRoom->move(&_player);
		_player.setPosition(3,3);
		_currentRoom = _rooms[1];
		_currentRoom->addActor(&_player);
		_eventDescriptions.append(_printer->printDead());
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
			_eventDescriptions.append(printCommands());
		}else {
			_eventDescriptions.append(_printer->printCouldNotUnderstandCommand(originalCommand));
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
				_eventDescriptions.append(_printer->printPickedUpWeapon(actor, item, oldWeapon));
				
			}else if(w==nullptr && d!= nullptr){
				d->healthUpgradeItem(item);
				_currentRoom->removeItem(item);
				_eventDescriptions.append(_printer->printPickedUpItem(actor, item));
			}
			return true;
		}else {
			_eventDescriptions.append(_printer->printCouldNotFindItem(item));
			return false;
		}
	}
	
	bool Game::search(){

		
		DangerousRoom *d = dynamic_cast<DangerousRoom*>(_currentRoom);
		bool isDangerousRoom = d!=nullptr;
		if(isDangerousRoom){
			int damage = d->getDamage();
			_player.getHit(damage);
		}
		_printer->printSearch(isDangerousRoom, _currentRoom);
	}

	
	bool Game::go(std::string direction, Actor* actor){
		Room* next = nullptr; 
		if(direction.compare("north")==0||direction.compare("n")==0){
			next = _currentRoom->getConnectedRoom(0); 
			if(next!=nullptr && actor->getName().compare("player")==0){
				_player.setPosition(_player.getXPosition(), (_player.getYPosition()-1));
			}
		}else if(direction.compare("west")==0||direction.compare("w")==0){
			next = _currentRoom->getConnectedRoom(3);
			if(next!=nullptr && actor->getName().compare("player")==0){
				_player.setPosition(_player.getXPosition()-1, (_player.getYPosition()));
			}
		}else if(direction.compare("south")==0||direction.compare("s")==0){
			next = _currentRoom->getConnectedRoom(2);
			if(next!=nullptr && actor->getName().compare("player")==0){
				_player.setPosition(_player.getXPosition(), (_player.getYPosition()+1));
			}
		}else if(direction.compare("east")==0||direction.compare("e")==0){
			next = _currentRoom->getConnectedRoom(1);
			if(next!=nullptr && actor->getName().compare("player")==0){
				_player.setPosition(_player.getXPosition()+1, (_player.getYPosition()));
			}
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
					_eventDescriptions.append("You fell down a hole, and you can't get back up. ");
				}
				_currentRoom = next; 
				Player* p = dynamic_cast<Player*>(actor);
			} else {
				_eventDescriptions.append(actor->getName());
				_eventDescriptions.append(" left the area.");
			}
			return true;
		}else {
			if(actor->getName().compare("player")==0)
				_eventDescriptions.append("No path here");
			return false;	
		}
	}
	
	bool Game::hit(std::string targetName, Actor* attacker){
		
		Dangerous* d = dynamic_cast<Dangerous*>(attacker);
		Player* p = dynamic_cast<Player*>(attacker);
		Actor* a = _currentRoom->getActor(targetName);
		if(a==nullptr && _currentRoom->getActors().size()==1) {
			a = _currentRoom->getActors()[0];
		}		

		if(a!=nullptr){
			Dangerous* dan = dynamic_cast<Dangerous*>(a);
			if(dan!=nullptr){
				_eventDescriptions.append( _printer->printAttacked(attacker->getName(), targetName, d->getWeapon()) );
				
				d->action(dan);
				if(dan->getLife()==0){
					if(targetName.compare("player")!=0){
						_currentRoom->addItem(dan->getWeapon()); 
						_currentRoom->removeActor(targetName);
						std::stringstream s;
						s<<targetName<<" died. Good job! He dropped his weapon. "<<std::endl;
						_eventDescriptions.append(_printer->printString(s.str()));
					}
					if(targetName.compare("dragon")==0){
						win = true; 
						return true;
					}
					if(attacker->getName().compare("player")==0){
						std::stringstream s;
						s<<"your new life: "<<d->getLife()<<" xp: "<<p->getXP()<<std::endl;
						_eventDescriptions.append(_printer->printString(s.str()));
					}
				}else{
					if(targetName.compare("player")!=0){
						std::stringstream s;
						s<<targetName<<"'s new life is "<<dan->getLife()<<std::endl; 
						_eventDescriptions.append(_printer->printString(s.str()));
					}
				}
				return true;
			}else{
				if(attacker->getName().compare("player")==0){
					std::stringstream s;
					s<<"Could not attack "<<targetName<<". It is friendly"<<std::endl;
					_eventDescriptions.append(_printer->printString(s.str()));
				}
				return false;
			}
		}else{
			if(attacker->getName().compare("player")==0){
				std::stringstream s;
				s<<"Could not find "<<targetName<<" to attack. Did you write something wrong?"<<std::endl;
				_eventDescriptions.append(_printer->printString(s.str()));
			}
			return false;
		}
		
		
	}
	
	bool Game::lookAt(std::string item){
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
			_eventDescriptions.append(descStream.str());
		}else if(a!=nullptr){
			_eventDescriptions.append(a->getDescription());
			_eventDescriptions.append("\n");
		}else {
			std::stringstream s;
			s<<"Could not find "<<item<<std::endl;
			_eventDescriptions.append(s.str());
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
			std::stringstream s;
			s<<"Can't talk to "<<text<<"."<<std::endl;
			_eventDescriptions.append(s.str());
		} else {
			std::stringstream s;
			s<<"Can't find a "<<text<<" to talk to."<<std::endl;
			_eventDescriptions.append(s.str());	
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

	std::string Game::printWelcome(){
		return _printer->printWelcome(&_player, _currentRoom);
	}

	std::string Game::printScreen(){
		return _printer->printScreen(&_player, _currentRoom);
	}

	void Game::clearScreen(){
		_printer->clearScreen();
	}
	
	std::string Game::printCommands(){
		return _printer->printCommands();
	}
	

	
	std::string Game::printWorld(){
		return _printer->printWorld(&_player);
	}

	std::string Game::printEvents(){
		std::string s = _eventDescriptions;
		_eventDescriptions = "";
		return s;
	}
   
}



int main(){
		labb3::Game game;
		game.init();
		std::cout<<game.printScreen();
		game.clearScreen();
		std::string command = "";
		command = game.readCommand();
		while(command.compare("exit")!=0 && !game.win){
			if(game.performCommand(command, game.getPlayer()) && command.substr(0, 2).compare("go")!=0){
				game.update();
			}
			if(game.win) break;
			std::cout<<game.printScreen();
			std::cout<<game.printEvents();
			game.clearScreen();
			command = game.readCommand();
		}
		if(game.win){
			std::cout<<"You are the coolest! You defeated the great dragon. You are winner!!! "<<std::endl;
			getline (std::cin, command);
		}  
		std::cout<<"Bye bye!"<<std::endl;
}
	
