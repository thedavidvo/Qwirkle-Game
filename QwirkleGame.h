
#ifndef ASSIGN2_QWIRKLEGAME_H
#define ASSIGN2_QWIRKLEGAME_H

#include "LinkedList.h"
#include "Player.h"
#include "Bag.h"
#include <string>
#include <vector>
#include "TileCodes.h"

typedef char BoardCoor;
class QwirkleGame
{

public:
  QwirkleGame();
  ~QwirkleGame();

  bool placeTile(std::string placement);
  void allocatePoints(int x, int y, Player* player);
  bool replaceTile(std::string replacement);
  void addPlayer(std::string name);
  void fillPlayerHands();
  void printBoard();
  bool checkPlacement(int x, int y, Tile* pos);
  std::string getBoard();
  std::vector<Player *> getPlayers();
  Bag *getBag();
  void setBoard(int x, int y, Tile* tile);
  void setCurrentPlayer(Player* player);
  Player* getCurrentPlayer();
  
  

  bool gameFinished();

private:
  int letterToNumber(char a);
  Tile *board[27][27];
  std::string boardToString;
  std::vector<Player *> players;
  Bag *bag;
  Player* currentP;
  std::vector<Player *> highScoring[5];
};

#endif // ASSIGN2_QWIRKLEGAME_H
