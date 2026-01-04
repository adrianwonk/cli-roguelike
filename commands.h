#pragma once
#include <stdio.h>
#include "Entity.h"

class Command
{
public:
	virtual ~Command() = default;
	virtual void execute() = 0;
};

class advanceLevel : public Command
{
public:
	advanceLevel() : level(0) {}
	virtual void execute() {
		// code for advancing
		printf("advancing level(%d->%d)\n", level, ++level);
	}

private:
	int level;
};

class attackCommand : public Command
{
public:
	attackCommand(Entity& from, Entity& to) :
		from(from), to(to)
	{}
	virtual void execute() {
		// code f
		from.attack(to, from.getDmg());
	}
private:
	Entity& from;
	Entity& to;
};
