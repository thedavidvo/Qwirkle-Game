
#ifndef ASSIGN2_BAG_H
#define ASSIGN2_BAG_H

#include <cstdlib>
#include "LinkedList.h"
#include "Tile.h"

class Bag {
public:

Bag();

void fillBag();
void shuffleBag();
Node* pickFromBag();
LinkedList* getList();
int getSize();
private:
  //must be stored as an ordered linked list
LinkedList* tileList;
int randomGeneration(int min, int max);

};

#endif // ASSIGN2_BAG_H
