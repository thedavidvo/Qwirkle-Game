
#include "Node.h"

Node::Node(Tile* t, Node* n)
{
   this->tile = t;
   this->next = n;
}

Node::Node(Node& other) :
   tile(other.tile),
   next(other.next)
{}

Tile* Node::getTile()
{
  return this->tile;
}

Node* Node::getNext()
{
  return next;
}

void Node::setNext(Node* a){
  next = a;
}
