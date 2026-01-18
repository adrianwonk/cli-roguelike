#pragma once
#include <string>
#include <vector>
using namespace std;

class statVector{
  public:
    statVector() : statsv(2)
      {}
    
    int getHP() const;
    int changeHP(int change);
    int getDMG() const;
    int changeDMG(int change);
  private:
    // { HP, DMG, ...}
    vector<int> statsv;
};

class Entity
{
public:
	virtual ~Entity() {}

	// * default damage is 3
	Entity(string n, int hp) :
		name(n), stats()
	{
    stats.changeHP(hp);
    stats.changeDMG(3);
  }
	
	// default functions for all entities, showing their HP, attacking other entities, and healing health.
	void attack(Entity&, int);
	virtual void printEntity();
  string getName () { return name; }
  statVector stats;
private:
	// basic values for a single entity.
	string name;
};
