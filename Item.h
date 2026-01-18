#pragma once
#include <string>
#include <vector>
#include "Entity.h"

using namespace std;

/* TODO: who owns this item?
      assuming that we keep items in a itemsList per entity, an edge exist from Entity to item.
      do we need an edge between item owner?
        item sets, item synergies
*/

/* TODO: every LIVE item 
 * */

// what does this item do? is there any SPECIAL modifications BESIDES stat changes?
struct Item{
    Entity& owner;
    StatVector deltaStat;
};
