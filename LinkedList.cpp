
#include "LinkedList.h"

LinkedList::LinkedList() : head(nullptr),
                           current(nullptr),
                           tail(nullptr)

{
  numOfNodes = 0;
}

LinkedList::~LinkedList()
{
}

void LinkedList::addNode(Tile *a)
{
  NodePtr node = new Node(a, nullptr);
  /* checks if the list is already empty
     * then go through the list, using next to
     * point to the next node
     * else, if empty, make the head the node
     */
  if (head != nullptr)
  {
    tail->setNext(node);
    tail = node;
    numOfNodes++;
  }
  else if (head == nullptr)
  {
    head = node;
    tail = node;
    numOfNodes++;
  }
  else if (head == tail)
  {
    tail->setNext(node);
    tail = node;
    head->setNext(tail);
    numOfNodes++;
  }
} //end of addNode
/* find node for the random int to pull out */
Node *LinkedList::findNode(int f)
{
  Node *temp = head;

  for (int count = 1; count <= f; count++)
  {

    temp = temp->getNext();
  }
  return temp;
}

void LinkedList::addAt(int i, Node *node)
{
  if (i > 0 && i < numOfNodes)
  { /* find the node  
    and then set the pointers according 
    */ 
    Node *ka = findNode(i);
    findNode(i - 1)->setNext(node);
    findNode(i - 1)->getNext()->setNext(ka);
    numOfNodes++;
  }
  else if (i == 0 && head != nullptr)
  { /*additional cases where we might 
    be at the head
    */
    node->setNext(head);
    head = node;
    numOfNodes++;
  }
  else if (i == (numOfNodes))
  {
    tail->setNext(node);
    tail->getNext()->setNext(nullptr);
    tail = tail->getNext();
    numOfNodes++;
  }
}

void LinkedList::addBack(Tile *data)
{ 
  Node *newNode = new Node(data, nullptr);
  tail->setNext(newNode);
  tail = tail->getNext();
  numOfNodes++;
}
/* delete selected tile pointer */
void LinkedList::deleteNode(int i)
{  
  if (i == 0)
  { 
    head = head->getNext();
    numOfNodes--;
  }
  else if (i == numOfNodes - 1)
  {
    deleteBack();
  }
  else
  {
    findNode(i - 1)->setNext(findNode(i + 1));
    numOfNodes--;
  } 

}

void LinkedList::deleteBack()
{

  tail = findNode(numOfNodes - 2);
  tail->setNext(nullptr);
  numOfNodes--;
}

void LinkedList::deleteFront()
{
 
  head = head->getNext();
  numOfNodes--;
}

int LinkedList::returnSize()
{
  return numOfNodes;
}

/* prints everything in the linked list */
void LinkedList::printLine()
{
  current = head;

  while (current->getNext() != nullptr )
  {
    current->getTile()->printTile();

    if (current->getNext()->getNext() != nullptr)
    {
      std::cout << ", ";
    }
    if (current->getNext()->getNext() == nullptr)
    {
      std::cout << ", ";
      current->getNext()->getTile()->printTile();
    }
    current = current->getNext();
  }

  if (head->getNext() == nullptr) 
  {
    std::cout<< head->getTile()->getTileDets();
  }

  std::cout << std::endl;
}
