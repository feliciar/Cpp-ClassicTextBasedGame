all : game

game :  game.o printer.o room.o weapon.o  player.o item.o friendly.o dangerous.o actor.o itemfile.o dangerousRoom.o friendlyRoom.o worldData.o
	g++ -g -o game printer.o itemfile.o game.o room.o weapon.o  player.o item.o friendly.o dangerous.o friendlyRoom.o dangerousRoom.o actor.o worldData.o -std=c++11
	
game.o : game.cpp game.h
	g++ -g -c game.cpp -std=c++11
	
printer.o : printer.cpp printer.h
	g++ -g -c printer.cpp -std=c++11
	
room.o : room.cpp room.h
	g++ -g -c  room.cpp -std=c++11
	
weapon.o : weapon.cpp weapon.h
	g++ -g -c   weapon.cpp -std=c++11
	
player.o : player.cpp player.h
	g++ -g -c    player.cpp -std=c++11
	
item.o : item.cpp item.h
	g++ -g -c     item.cpp -std=c++11
	
friendly.o : friendly.cpp friendly.h
	g++ -g -c      friendly.cpp -std=c++11
	
dangerous.o : dangerous.cpp dangerous.h
	g++ -g -c       dangerous.cpp -std=c++11
	
actor.o : actor.cpp actor.h
	g++ -g -c        actor.cpp -std=c++11

itemfile.o : itemfile.cpp itemfile.h
	g++ -g -c         itemfile.cpp -std=c++11
	
dangerousRoom.o : dangerousRoom.cpp dangerousRoom.h
	g++ -g -c          dangerousRoom.cpp -std=c++11
	
friendlyRoom.o : friendlyRoom.cpp friendlyRoom.h
	g++ -g -c           friendlyRoom.cpp -std=c++11
	
worldData.o : worldData.cpp worldData.h
	g++ -g -c 				worldData.cpp -std=c++11