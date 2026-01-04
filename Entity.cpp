#include "Entity.h"
#include <stdio.h>
using namespace std;

int Entity::getHP() const{
	return health;
}

void Entity::printEntity() {
	printf("--Entity--------\n"
			"Name: %s\n"
			"Health: %d\n"
			"Abilities: %s\n"
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
