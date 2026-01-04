#pragma once
#include <string>
using namespace std;
class Entity
{
public:
	virtual ~Entity() {}

	// * default damage is 3
	Entity(string n, int hp) :
		health(hp),
		name(n), dmg(3)
	{}
	
	// default functions for all entities, showing their HP, attacking other entities, and healing health.
	int getHP() const;
	void attack(Entity&, int);
	void heal(int);
	virtual void printEntity();
	int getDmg();

private:
	// basic values for a single entity.
	string name;
	int health;
	int dmg; // *
};
