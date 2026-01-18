#include <iostream>
#include "Entity.h"
#include "commands.h"
#include <vector>
#include <algorithm>
#include <memory>
#include <cmath>
#include <ncurses.h>
#include <signal.h>

// text based D-Crawler??
using namespace std;

void takeUserInput(vector<unique_ptr<Command>>& actionList, int startIndex, int& pageNum);
void print8ActionList(vector<unique_ptr<Command>>& actionList, int startIndex, int pageNum, int totalPageNum);
int getTotalPageNum(vector<unique_ptr<Command>>& list);

int main(){
  // ncurses window setup.
  initscr(); // allocates memory for the screen.
  cbreak();     // disables buffering of input, but retains control signals.
  noecho();
  // store available actions this turn
  int level { 1 };
  string outputBuff;
  vector<unique_ptr<Command>> actionList{};
  actionList.push_back(make_unique<printCommand>("what the fuck", outputBuff));
  actionList.push_back(make_unique<printCommand>("hello world", outputBuff));
  actionList.push_back(make_unique<printCommand>("don't be a dickhead", outputBuff));
  actionList.push_back(make_unique<createCommand>(actionList, outputBuff));
  actionList.push_back(make_unique<advanceLevel>(level, outputBuff));
  int pageNum { 0 }; // each page shows 8 items.

	Entity player("player", 5);
	int input { 0 };
  

	while (1){
    // Guards to avoid values going out of range.
    // actionList exceeding integer maximum
    if (actionList.size() > INT_MAX) {
      fprintf(stderr, "list of commands exceeded maximum\n");

      exit(-1);
    }

		// pageNum out of range
    int startIndex = pageNum*8;
    if (startIndex > (int) actionList.size() - 1 ) { 
      fprintf(stderr, "pageNum(%d) has exceeded the maximum size(%d)\n", pageNum, actionList.size());
      return -1;
    }
    ///////////////////////////// end guards

    // display current environment
    clear();
    player.printEntity();
    printw("Output:\n%s\n\n", outputBuff.c_str());
    print8ActionList(actionList, startIndex, pageNum, getTotalPageNum(actionList));
    refresh();

    // take user reaction and execute commands
    takeUserInput(actionList, startIndex, pageNum);
	}
  endwin();
}

void takeUserInput(vector<unique_ptr<Command>>& actionList, int startIndex, int& pageNum){
    // take user input
		int x { 6 };
    while (1){
      // make sure input type matches
      while (1){
        x = getch();
        if ( x>='0' && x<='9' ) break;
        printw ("wrong input man, please input 0-9\n");
      }

      // number exceeds the last command in the list (happens when we have fewer than 8 commands on screen)
      if ('1' <= x && x <= '8' && startIndex + x - 48 - 1 >= (int) actionList.size()) {
        printw("not a valid input. Please try again\n");
        continue;
      }

      // trying to move from page 1 to page 0
      if (x == '9' && pageNum+1 <= 1){
        printw("already at earliest page. Please try again\n");
        continue;
      }
      
      // trying to move from page MAX to page MAX + 1
      if (x == '0' && pageNum+1 >= getTotalPageNum(actionList)){
        printw("already at last page. Please try again\n");
        continue;
      }
      break;
    }

    // map the input number to execute the associated command
    switch (x) {
      case '1':
        actionList[startIndex + 0]->execute();
        break;
      case '2':
        actionList[startIndex + 1]->execute();
        break;
      case '3':
        actionList[startIndex + 2]->execute();
        break;
      case '4':
        actionList[startIndex + 3]->execute();
        break;
      case '5':
        actionList[startIndex + 4]->execute();
        break;
      case '6':
        actionList[startIndex + 5]->execute();
        break;
      case '7':
        actionList[startIndex + 6]->execute();
        break;
      case '8':
        actionList[startIndex + 7]->execute();
        break;
      case '9':
        if (pageNum > 0) pageNum--;
        break;
      case '0':
        if (startIndex + 8 < (int) actionList.size()) pageNum++;
        break;
    }
}

int getTotalPageNum(vector<unique_ptr<Command>>& list){
  return ceil((float) list.size() / 8);
}

void print8ActionList(vector<unique_ptr<Command>>& actionList, int startIndex, int pageNum, int totalPageNum){
  int num = 1;
  for (int i = startIndex; i < min(startIndex + 8, (int) actionList.size()); i++) {
    printw ("%d. %s\n", num++, actionList[i]->getIdentifier().c_str());
  }
  printw("Page [%d,%d]\n", pageNum+1, totalPageNum);
  printw("9. last page\n");
  printw("0. next page\n");
}

