
#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include "LinkedList.h"
#include "Tile.h"
#include <string>
#include "Bag.h"

class Player {
public:

   Player(std::string name, int score);
   
   int countTilesInHand();
   void printHand();
   void fillHand(Bag* bag);
   std::string getName();
   int getScore();
   void setScore(int points);
   void resetTurn();
   
   LinkedList* getHand();

   void setPlayerName(std::string name);
   void setPlayerScore(int score);
   void setPlayerHand(Tile* tile);

 
private:
   LinkedList* hand;
   std::string playerName;
   int score;
};

#endif // ASSIGN2_NODE_H
