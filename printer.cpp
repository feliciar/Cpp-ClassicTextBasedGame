#include "printer.h"
#include <iostream>
#include <sstream>

namespace labb3{



	std::string Printer::printWelcome(const Player * player, Room * currentRoom){
		_numPrintedLines = 0;
		std::string string = player->printPlayerInfo();
		_numPrintedLines += findNumberOfLines(string);
		string.append("\nWelcome! \n");
		string.append("With no recollection of where you are or who you are,\n");
		string.append("you hear a distant roar to the north. \n");
		
		string.append("If you are confused just say 'help', or try to go somewhere. \n");
		std::string roomInfo = currentRoom->printContent();
		string.append(roomInfo);

		_numPrintedLines += 6 + findNumberOfLines(roomInfo);
		return string;
	}

	std::string Printer::printCommands(){
		std::string printString =  "go [direction]\t to go somewhere\n";
		printString.append("hit [enemy]\t to attack something\n");
		printString.append("pick up [item]\t to pick something up\n");
		printString.append("look at [thing]\t to look closer at something, to find out more\n");
		printString.append("talk to [friend] to talk to someone\n");
		printString.append("search\t\t to see what is around you\n");
		printString.append("sleep\t\t to rest and regain some health");
		_numPrintedLines += 7;
		return printString;		
	}


	/*
			       ________   
			 _____|  ===   |_ 
			|        ~~~     |   
			|     ~~~      |||
			~~~~~~         |  
			      444   444   
			      444444444   
	*/
	std::string Printer::printWorld(const Player * player){
		std::string worldStrings[7];
		worldStrings[0] = "       ________   ";
		worldStrings[1] = " _____|  ===   |_ ";
		worldStrings[2] = "|        ~~~     |";
		worldStrings[3] = "|     ~~~      |||";
		worldStrings[4] = "~~~~~~         |  ";
		worldStrings[5] = "      444   444   ";
		worldStrings[6] = "      444444444   ";

		int x = player->getXPosition();
		if(x<0 || x>=7)
			x=0;
		int y = player->getYPosition();
		worldStrings[y+1][x*3+1] = '8';

		std::string str = "";
		for(int i =0; i<7; ++i){
			str.append(worldStrings[i]);
			str.append("\n");
		}
		_numPrintedLines += 7;
		return str;
	}

	std::string Printer::printScreen(const Player * player, Room * currentRoom){
		std::string string ="###------------###------------###------------###------------###------------###\n";
		std::stringstream descStream;
		descStream<<player->printPlayerInfo()<<std::endl;
		string.append(descStream.str());
		string.append(this->printWorld(player));
		string.append(currentRoom->printContent());
		_numPrintedLines += 3;
		return string;
	}

	void Printer::clearScreen(){
		int newLines = 22-_numPrintedLines;
		_numPrintedLines = 0;
		for(int i=0; i<newLines; ++i){
			std::cout<<""<<std::endl;
		}
		
	}

	std::string Printer::printPickedUpWeapon(Actor * actor, std::string item, std::string oldWeapon){
		std::stringstream descStream;
		if(actor->getName().compare("player")==0){
			descStream<<"You picked up "<<item<<" and left behind your old "<<oldWeapon<<std::endl;
		} else {
			descStream<<actor->getName()<<" picked up "<<item<<" and left behind it's old "<<oldWeapon<<std::endl;
		}
		_numPrintedLines += 1;
		return descStream.str();
	}

	std::string Printer::printPickedUpItem(Actor * actor, std::string item){
		std::stringstream descStream;
		if(actor->getName().compare("player")==0){
			descStream<<"You picked up "<<item<<" and increased your max health by 10"<<std::endl;
		} else {
			descStream<<actor->getName()<<" picked up " <<item<<std::endl;
		}
		_numPrintedLines += 1;
		return descStream.str();
	}

	std::string Printer::printCouldNotFindItem(std::string item){
		std::stringstream descStream;
		descStream<<"Could not find item "<<item<<std::endl;
		_numPrintedLines += 1;
		return descStream.str();
	}

	int Printer::findNumberOfLines(std::string string)const{
		int numLines=0;
		for(char& c : string) {
    		if(c=='\n'){
    			++numLines;
    		}
		}
	}




}