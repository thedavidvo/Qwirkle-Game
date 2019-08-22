
#include "Bag.h"
#include <random>

Bag::Bag()
{
  tileList = new LinkedList();
} //END OF CONSTRUCTOR

void Bag::fillBag()
{
  Tile *t;
  // Iterate through colours
  for (int i = 0; i < 3; i++)
  {
    for (int i = 1; i <= 6; i++)
    {
      t = new Tile(RED, i);
      tileList->addNode(t);

      t = new Tile(ORANGE, i);
      tileList->addNode(t);

      t = new Tile(YELLOW, i);
      tileList->addNode(t);

      t = new Tile(GREEN, i);
      tileList->addNode(t);

      t = new Tile(BLUE, i);
      tileList->addNode(t);

      t = new Tile(PURPLE, i);
      tileList->addNode(t);
    }
  }
}
void Bag::shuffleBag()
{
  for (int i = 0; i < 108; i++)
  {
    int random = randomGeneration(0, 107);
    if (random == 0)
    {
      tileList->addBack(tileList->findNode(random)->getTile());
      tileList->deleteFront();
    }
    else
    {
      tileList->addBack(tileList->findNode(random)->getTile());
      tileList->deleteNode(random);
    }
  }
}

Node *Bag::pickFromBag()
{

  Node *add = tileList->findNode(0);
  tileList->deleteFront();
  return add;
}

LinkedList *Bag::getList()
{
  return tileList;
}

int Bag::getSize()
{
  return tileList->returnSize();
}

int Bag::randomGeneration(int min, int max)
{

  std::random_device engine;
  std::uniform_int_distribution<int> uniform_dist(min, max);

  int randomNo = 0;
  for (int i = 0; i != max; ++i)
  {

    randomNo = uniform_dist(engine);
  }
  return randomNo;
}
