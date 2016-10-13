#include "room.cpp"
#include <iostream>
#include "actor.cpp"
#include "item.cpp"

namespace labb3{
	void test1(){
		
	}
	
	void test2(){
		Room r("Du är i ett fint rum"); 
		std::cout<<r.printContent()<<std::endl;
	}



	void test(){
		test1();
		test2();
	}
	
	

}
int main(){
	labb3::test();
}