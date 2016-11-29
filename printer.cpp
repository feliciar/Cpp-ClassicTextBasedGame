#include "printer.h"
#include <iostream>
#include <sstream>
#include <windows.h>
#include <locale>

namespace labb3{

	Printer::Printer(){
		_numPrintedLines = 0;
		
		_operatingSystem = getOS();
		//setupConsole();
	}

	std::string Printer::printWelcome(const Player * player, Room * currentRoom){
		_numPrintedLines = 0;
		std::string string = printPlayer(player);
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
		
		std::string playerInfo = printPlayer(player);
		playerInfo.append("\n");
		string.append(playerInfo);
		_numPrintedLines += findNumberOfLines(playerInfo);

		string.append(this->printWorld(player));

		string.append(printRoomContent(currentRoom));
		return string;
	}

	void Printer::clearScreen(){
		int newLines = getScreenHeight()-_numPrintedLines-1;
		_numPrintedLines = 0;
		for(int i=0; i<newLines; ++i){
			std::cout<<""<<std::endl;
		}	
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

	std::string Printer::printPlayer(const Player * player){
		Weapon* wep = dynamic_cast<Weapon*>(ItemFile::getItems().find(player->getWeapon())->second);
		std::stringstream descStream;
		descStream<<player->getLife()<<"/"<<player->getMaxHealth()<<" <3 "<<" \t"<<player->getXP()<<" XP"<<" \t\tWEAPON: "<<*wep;
		return descStream.str();
	}

	std::string Printer::printPickedUpWeapon(Actor * actor, std::string item, std::string oldWeapon){
		std::stringstream descStream;
		if(actor->getName().compare("player")==0){
			//descStream<<"You picked up "<<item<<" and left behind your old "<<oldWeapon<<std::endl;
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

	std::string Printer::printGotHit(int damage){
		std::stringstream s; 
		s<<"You got hit! You lost "<<damage<<" life.\n";
		_numPrintedLines += 1;
		return s.str();
	}

	std::string Printer::printDead(){
		_numPrintedLines += 2;
		return "You died! \nThe next thing you remember is waking up at the ground next to the campfire. \n";
	}

	std::string Printer::printHit(std::string targetName, Actor * attacker){

	}

	std::string Printer::printAttacked(std::string attacker, std::string target, std::string weapon){
		std::stringstream s;
		if(attacker.compare("player")==0){
			//s<<"You attacked "<<target<<" with your "<<weapon<<std::endl;
		}
		else if ( target.compare("player")!=0){
			s<<attacker<<" attacked "<<target<<" with "<<weapon<<std::endl;
		}
		++_numPrintedLines;
		return s.str();
	}

	std::string Printer::printRoomContent(Room * room, std::string command){
		std::string roomInfo = room->printContent(command);
		roomInfo.append("\n");
		_numPrintedLines += findNumberOfLines(roomInfo);
		return roomInfo;
	}

	std::string Printer::printSearch(bool isDangerousRoom, Room * room){
		std::string string="";
		if(isDangerousRoom){
			string.append(printRoomContent(room, "search"));
			string.append("You take damage from the dangerous spiders and rats lurking in the shadows. \n");
			++_numPrintedLines;
		}else {
			string.append(printRoomContent(room, "search"));
		}
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


	std::string Printer::printString(std::string string){
		_numPrintedLines += findNumberOfLines(string);
		return string;
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

	int Printer::getScreenWidth()const{
		int columns = 20;
		if(_operatingSystem.compare("Windows")==0){
			CONSOLE_SCREEN_BUFFER_INFO csbi;
		    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		}
		return columns;
	}

	int Printer::getScreenHeight()const{
		int rows = 10;
		if(_operatingSystem.compare("Windows")==0){
			CONSOLE_SCREEN_BUFFER_INFO csbi;
		    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		}
	    return rows;
	}

	std::string Printer::getOS()const{
	    #ifdef _WIN32
	    	return "Windows";
	    #elif defined(_WIN64)
	    	return "Windows";
	    #elif __unix || __unix__
	    	return "Unix";
	    #elif __APPLE__ || __MACH__
	    	return "Mac OSX";
	    #elif __linux__
	    	return "Linux";
	    #elif __FreeBSD__
	    	return "FreeBSD";
	    #else
	    	return "Other";
	    #endif
	}

	void Printer::setupConsole()const{


		if(_operatingSystem.compare("Windows")==0){
			SetConsoleCP(CP_UTF8);
			SetConsoleOutputCP(CP_UTF8);


			CONSOLE_FONT_INFOEX cfix;
	        cfix.cbSize       = sizeof(cfix);
	        cfix.nFont        = 12;
	        cfix.dwFontSize.X = 8;
	        cfix.dwFontSize.Y = 14;
	        cfix.FontFamily   = FF_DONTCARE;
	        cfix.FontWeight   = 400;  // normal weight
	        //lstrcpy(cfix.FaceName, TEXT("Lucida Console"));

			//SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &cfix);
		}
		char ex = '\3';

		std::cout<<ex<<std::endl;
		std::cout<< "♥" << std::endl;
		std::cout<< " "<<std::endl;
		std::cout<<"\u2665"<<std::endl;

		const char heart[] = "\xe2\x99\xa5";
		std::cout<<heart<<std::endl;

		wchar_t h[] = L"\u2665";
		setlocale(LC_ALL, "");
    	std::wcout << heart << L'\n';

    	std::cout<<(char)3<<std::endl;
    	std::cout <<(char)6<<std::endl;
    	std::cout<<"\u9829"<<std::endl;
		//if (IsValidCodePage(CP_UTF8))
		//	std::cout<<"Good"<<std::endl;



	}





}