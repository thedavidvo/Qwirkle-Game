
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node {
public:

   Node(Tile* t, Node* n);
   Node(Node& other);

   Tile* getTile();
   Node* getNext();
   void setNext(Node* a);

/* i made these private??, and are these arrays? */
private:
   Tile*    tile;
   Node*    next;
};

typedef Node* NodePtr;
#endif // ASSIGN2_NODE_H
