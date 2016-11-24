#include "printer.h"
#include <iostream>
#include <sstream>
#include <windows.h>

namespace labb3{

	Printer::Printer(){
		_numPrintedLines = 0;
	}

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
		std::string printString = "The available commands are: \n";
		printString.append("go [direction]\t to go somewhere\n");
		printString.append("hit [enemy]\t to attack something\n");
		printString.append("pick up [item]\t to pick something up\n");
		printString.append("look at [thing]\t to look closer at something, to find out more\n");
		printString.append("talk to [friend] to talk to someone\n");
		printString.append("search\t\t to see what is around you\n");
		printString.append("sleep\t\t to rest and regain some health\n");
		_numPrintedLines += 8;
		return printString;		
	}

	std::string Printer::printCouldNotUnderstandCommand(std::string command){
		std::stringstream s; 
		s<<"did not understand command "<<command<<std::endl;
		++_numPrintedLines;
		return s.str();
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
		int screenWidth = getScreenWidth();
		std::string string= ""; 
		for(int i=0; i<screenWidth-1; ++i){
			if(i%10==0 || (i-1)%10==0 || (i-2)%10==0){
				string.append("#");
			}else{
				string.append("-");
			}
		}
		string.append("\n");
		++_numPrintedLines;
		
		std::string playerInfo = player->printPlayerInfo();
		playerInfo.append("\n");
		string.append(playerInfo);
		_numPrintedLines += findNumberOfLines(playerInfo);

		string.append(this->printWorld(player));

		std::string roomInfo = currentRoom->printContent();
		string.append(roomInfo);
		_numPrintedLines += findNumberOfLines(roomInfo);
		return string;
	}

	void Printer::clearScreen(){
		int newLines = getScreenHeight()-_numPrintedLines-1;
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

	std::string Printer::printDead(){
		_numPrintedLines += 2;
		return "You died! \nThe next thing you remember is waking up at the ground next to the campfire. \n";
	}

	std::string Printer::printRoomContent(Room * room, std::string command){
		std::string roomInfo = room->printContent(command);
		roomInfo.append("\n");
		_numPrintedLines += findNumberOfLines(roomInfo);
		return roomInfo;
	}

	int Printer::findNumberOfLines(std::string string)const{
		int numLines=0;
		for(char& c : string) {
    		if(c=='\n'){
    			++numLines;
    		}
		}
		return numLines;
	}

	std::string Printer::printGotHit(int damage){
		std::stringstream s; 
		s<<"You got hit! You lost "<<damage<<" life.\n";
		_numPrintedLines += 1;
		return s.str();
	}



	int Printer::getScreenWidth()const{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		int columns;
	    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		return columns;
	}

	int Printer::getScreenHeight()const{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		int rows;
	    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	    return rows;
	}





}