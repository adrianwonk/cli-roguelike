#include "Entity.h"
#include <stdio.h>
#include <ncurses.h>
using namespace std;

void Entity::printEntity() {
	printw("--Entity--------\n"
			"Name: %s\n"
			"Health: %d\n"
			"Abilities: %s\n\n"
			, name.c_str(), stats.getHP(), "nothing");
}

void Entity::attack(Entity& other, int amt) {
	other.stats.changeHP(-amt);
}

int statVector::getHP() const{
  return statsv[0];
}

int statVector::changeHP(int change){
  statsv[0] += change;
  return statsv[0];
}

int statVector::getDMG() const{
  return statsv[1];
}

int statVector::changeDMG(int change) {
  statsv[1] += change;
  return statsv[1];
}
