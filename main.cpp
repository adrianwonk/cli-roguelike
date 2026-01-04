#include <iostream>
#include "Entity.h"
#include "commands.h"
// text based D-Crawler??
using namespace std;

int main(){
	Entity player("player", 5);
	int input (0);

	while (1){
		player.printEntity();
		printf("--What would you like to do?--\n"
				"1.\n"
				"2.\n"
				);
		scanf("%d", &input);

	}
}


