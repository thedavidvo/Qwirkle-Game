
#include "Player.h"

//TODO  Implement the player
Player::Player(std::string name, int score)
{
  hand = new LinkedList();
  playerName = name;
  this->score = score;
}

//Returns the side of the player's hand
int Player::countTilesInHand()
{
  return hand->returnSize();
}

void Player::printHand()
{
  return hand->printLine();
}

std::string Player::getName()
{
  return playerName;
}

int Player::getScore()
{
  return score;
}

void Player::setScore(int points)
{
  score += points;
}

//fills the hands of the player
void Player::fillHand(Bag *bag)
{
  for (int i = 0; i < 6; i++)
  {
    hand->addNode(bag->pickFromBag()->getTile());
  }
}

LinkedList *Player::getHand()
{
  return hand;
}

