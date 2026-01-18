#pragma once
#include <iostream>
#include <stdio.h>
#include "Entity.h"
#include <string>
#include <format>
#include <stdlib.h>
#include <memory>
#include <vector>

using namespace std;

class Command
{
public:
	virtual ~Command() = default;
	virtual void execute() = 0;
  virtual string getIdentifier() = 0;
};

// TODO: try to run virtual function that isn't defined (func = 0), see what happens.
class printCommand : public Command
{
// This class returns an output to stdout, and performs implementation defined sideEffects() when executed.
// There is a customIdentifier which overrides the standard "print me!" label for UI.
// literalOutput can be empty, allowing users to construct their own output at runtime.
public:
  printCommand(string& outputBuff) : outputBuff(outputBuff), literalOutput(""), customIdentifier("") {}
  printCommand(string out, string& outputBuff) : outputBuff(outputBuff), literalOutput(out), customIdentifier("") {}
  printCommand(string out, string id, string& outputBuff) : outputBuff(outputBuff), literalOutput(out), customIdentifier(id) {} 

  // returns string literal to stdout. Should be overridden by inherited classes if using runtime output.
  virtual string output() {
    if (literalOutput == "") {
      fprintf(stderr, "uninitialised literalOutput, output base function not overridden.\n");
      exit(1);
    }
    else return literalOutput;
  }

  // called after writing to stdout.
  virtual void sideEffects() {};

  // called to cnstruct the UI. Can be overidden per inherited class
  virtual string getIdentifier(){
    return (customIdentifier == "") ? "print me!" : customIdentifier;
  }

  // hide from inherited classes. Outputs to stdout, and performs side effects.
  void execute(){
    outputBuff = output();
    sideEffects();
  }
private:
  string literalOutput;
  string customIdentifier;
  string& outputBuff;
};

class advanceLevel : public printCommand
{
public:
	advanceLevel(int& l, string& outputBuff) :
    printCommand(outputBuff),
    level(l)
  {}
  string output() {
    return format("advancing level ({} -> {})", level, level + 1);
  }
	void sideEffects(){
    level++;
  }
  string getIdentifier() {
    return "advance level";
  }
private:
	int& level;
};

// this command will be created at run-time whenever an enemy ENTERS the player's scope, and will be destroyed whenever an enemy LEAVES player scope.
class attackCommand : public printCommand
{
public:
	attackCommand(Entity& from, Entity& to, string& outputBuff) :
    printCommand(outputBuff),
		from(from), to(to)
	{}
  string output(){
    return from.getName() + " just attacked " + to.getName() + "!";
  }
  void sideEffects(){
    from.attack(to, from.stats.getDMG());
  }
  string getIdentifier(){
    return "attack " + to.getName();
  }
private:
	Entity& from;
	Entity& to;
};

class createCommand : public  printCommand
{
public:
  createCommand( vector<unique_ptr<Command>>& ref, string& outputBuff ) :outputBuff(outputBuff), printCommand(outputBuff), list(ref), index(1){}

  string output(){
    return "we made a new command";
  }

  string getIdentifier(){
    return "make new command";
  }
  
  void sideEffects() {
    list.push_back(make_unique<printCommand>( format("we created this command! num: {}", index), format("custom {}",index), outputBuff ));
    index++;
  }

private:
  string& outputBuff;
  vector<unique_ptr<Command>>& list;
  size_t index;
};
