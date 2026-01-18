#include "Entity.h"
#include <stdio.h>
#include <ncurses.h>
using namespace std;

int Entity::getHP() const{
	return health;
}

void Entity::printEntity() {
	printw("--Entity--------\n"
			"Name: %s\n"
			"Health: %d\n"
			"Abilities: %s\n\n"
			, name.c_str(), health, "nothing");
}

void Entity::heal(int amt) {
	health += amt;
}

void Entity::attack(Entity& other, int amt) {
	other.health -= amt;
}

int Entity::getDmg() {
	return dmg;
}
