
#include "QwirkleGame.h"
#include <iostream>

#define MAX_ROWS 25
#define MAX_COLS 25

/* This class is for the board, where moves are made and pieces set into the board
 *
 * METHODS INCLUDE:
 *   - place tile (on the board) -> put tile on board, remove from hand
 *
 *   - replace a tile
 *
 *   - checking the trend (same shape or same color)
 *
 */

QwirkleGame::QwirkleGame()
{
  this->bag = new Bag();

  for (int i = 0; i < 26; i++)
  {

    for (int j = 0; j < 26; j++)
    {

      board[i][j] = nullptr;
    }
  }
}
QwirkleGame::~QwirkleGame()
{
  delete bag;
}

/*
  Placing the tile takes in the string of the user's input, which is then allocated to 3 substrings.
  The first substring is parsed to a tile, where we create the tile, then the second and third substring
  is parsed to an int, where it acts as the coordinates of the placement. We then have check conditions
  such as allocating points, checking for valid tile, and checking the bag.
*/
bool QwirkleGame::placeTile(std::string placement)
{
  bool check = false;
  //checking if the input/string was a valid length
  if ( placement.length() < 8 ) {

   std::cout << "You have entered an invalid input" << std::endl;

   return false;
  }
  std::string tile = placement.substr(1, 2);
  std::string x = placement.substr(7, 1);
  std::string y = placement.substr(8, 1);
  std::string y2;
  int twoDigit;
  /*
  convert the letter to number with the letter2number method
  we need to hold the tile in the hand so it can be used by the methods
  */
  std::string code = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  bool p = (code.find(x) != std::string::npos);
  Tile *tileInHand = nullptr;
  int y2n = letterToNumber(*x.c_str());
  int x2n = std::atoi(y.c_str());
  int i = 0;
 /*we need to check for double digit numbers since the board is larger than 10 done
   done below
 */
  if (placement.length() > 9)
  {
    y2 = placement.substr(9, 1);
    twoDigit = (10 * x2n) + (std::atoi(y2.c_str()));
    x2n = twoDigit;
  }

  if (p == false)
  {
    std::cout << "Incorrect tile entered";
    return false;
  }
  else if (x2n < 26 && y2n < 26) //keeping the coordinates from going out of bounds
  {
    /*
    **PSEUDO**

     - check if the tile exist inside the players hand
     - obtain this tile and then check whether the tile is placement is valid (within qwirkle rules)
     - remove tile from the hand
     - remove a tile from the bag after the tile is placed and add that tile to the hand
     - return true;

    */
    while (tileInHand == nullptr && i < 6)
    {

      if (currentP->getHand()->findNode(i)->getTile()->getTileDets() == tile)
      {
        tileInHand = currentP->getHand()->findNode(i)->getTile();
        if ((checkPlacement(y2n, x2n, tileInHand)) == true)
        {
          board[y2n][x2n] = tileInHand;

          currentP->getHand()->deleteNode(i);

          if (bag->getSize() != 0)
          {
            bag->getList()->addBack(tileInHand);
            Node *pickedTile = bag->pickFromBag();
            currentP->getHand()->addAt(i, pickedTile);
          }
          else
          {
            std::cout << "The bag is empty" << std::endl;
          }

          allocatePoints(y2n, x2n, currentP);
          return true;
        }
        else
          std::cout << "Not a legal placement" << std::endl;
        return false;
      }
      i++;
    }
  }
//error messages incase user makes a mistake
  if (tileInHand == nullptr)
  {
    std::cout << "The tile you have entered does not exist" << std::endl;
  }
  else if (std::atoi(y.c_str()) > 26 && letterToNumber(*x.c_str()) > 26)
  {
    std::cout << "The tile you have entered is beyond the boundaries of the board" << std::endl;
  }

  return check;
}

/*
  Allocate points is a method that checks the horizontal and vertical surroundings of the placed tile,
  utilising a counter that incremements if there is a piece.
  We then use the counter to add it to the total points initialised locally, then set it to the player
  that was sent into the parameters
*/
void QwirkleGame::allocatePoints(int x, int y, Player *player)
{
  int trackVer = 0;
  int trackHor = 0;

  /*
    **PSUEDO**

     - initiate decrementation and incremetation loops so that we can count the incoming tiles on each side of the
     tile we have placed
     - count tiles which are not null
     - if the we encountered a null in the chain the tracker is set to 0;
   */

  for (int i = 0; i < y; i++)
  {
    if (board[x][i] != nullptr && i <= y)
    {
      trackHor++;
    }
    else if (board[x][i] == nullptr)
    {
      trackHor = 0;
    }
  }
  for (int i = 26; i > y; i--)
  {

    if (board[x][i] != nullptr && i >= y)
    {
      trackHor++;
    }
    else if (board[x][i] == nullptr && trackHor < 1)
    {
      trackHor = 0;
    }
  }
  for (int i = 0; i < x; i++)
  {

    if (board[i][y] != nullptr && i <= x)
    {
      trackVer++;
    }
    else if (board[x][i] == nullptr)
    {
      trackVer = 0;
    }
  }
  for (int i = 26; i > x; i--)
  {
    if (board[i][y] != nullptr && i >= y)
    {
      trackVer++;
    }
    else if (board[i][y] == nullptr && trackVer < 1)
    {
      trackVer = 0;
    }
  }

  //Score is calculated for surrounding nodes
  int totalpoints = trackHor + trackVer + 1;

  //Qwirkle accounts for 6 points
  if (trackHor == 5 || trackVer == 5)
  {
    std::cout << "QWIRKLE!!!" << std::endl;
    totalpoints += 6;
  }

  //If a tile is placed in two lines, that tile we placed is 2 points
  if(trackHor > 0 && trackVer > 0)
  {
    totalpoints += 2;
  }

  //Setting the score
  player->setScore(totalpoints);

}
/*
  Replacing the tile takes in a string, where the string is turned to a substring.
  The tile being replaced will then get added back to the list (in the bag) and the player will
  pick the bag from the front of the list (in the bag).
  Will also check if bag is empty,
  IF empty, then return nothing, cal that bag is empty and unable to replace tile.
  We assume turn is taken.
*/
bool QwirkleGame::replaceTile(std::string replacement)
{
  Tile *tileInHand = nullptr;
  bool check = false;
  std::string tile = replacement.substr(1, 2);

  if (replacement.length() == 3)
  {
    for (int k = 0; k < currentP->getHand()->returnSize(); k++)
    {
      if (currentP->getHand()->findNode(k)->getTile()->getTileDets() == tile)
      {
        tileInHand = currentP->getHand()->findNode(k)->getTile();
        currentP->getHand()->deleteNode(k);
        if (bag->getSize() != 0)
        {
          bag->getList()->addBack(tileInHand);
          Node *pickedTile = bag->pickFromBag();
          currentP->getHand()->addAt(k, pickedTile);
        }
        else
        {
          std::cout << "Bag is empty, unable to replace tile." << std::endl;
        }

        return true;
      }
    }
  }
  else if (tileInHand == nullptr)
  {
    std::cout << "You have entered an invalid tile";
  }

  return check;
}
//gets the bag
Bag *QwirkleGame::getBag()
{
  return bag;
}
//adds player to the game
void QwirkleGame::addPlayer(std::string name)
{
  Player *p = new Player(name, 0);
  players.push_back(p);
}
//gets the list of players
std::vector<Player *> QwirkleGame::getPlayers()
{
  return players;
}
//fills the hands of the player from the bag
void QwirkleGame::fillPlayerHands()
{
  for (int i = 0; i < players.size(); i++)
  {
    players.at(i)->fillHand(bag);
  }
}
//prints the board of the qwirkle game
void QwirkleGame::printBoard()
{
  std::cout << "  0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25" << std::endl;
  std::cout << " ------------------------------------------------------------------------------- " << std::endl;

  boardToString = "  0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 \n ------------------------------------------------------------------------------- \n";

  char a = 'A';
  for (int i = 0; i < 26; i++)
  {
    for (int j = 0; j < 26; j++)
    {
      if (j == 0)
      {
        std::cout << a;
        boardToString += a;
        a++;
      }
      std::cout << "|";
      boardToString += "|";

      if (board[i][j] == nullptr)
      {
        std::cout << "  ";
        boardToString += "  ";
      }
      else
      {
        std::cout << board[i][j]->getTileDets();
        boardToString += board[i][j]->getTileDets();
      }
      if (j == 25)
      {
        std::cout << "|";
        boardToString += "|";
      }
    }
    std::cout << std::endl;
    boardToString += "\n";
  }
}
// board Coordinate converting A = 0, B = 1 ... z = 25
int QwirkleGame::letterToNumber(char word)
{
  int x = word;

  if (!isupper(static_cast<unsigned char>(word)) == true)
  {
    x = std::tolower(word);
  }
  return x - 65;
}

//Gets board
std::string QwirkleGame::getBoard()
{
  return boardToString;
}

bool QwirkleGame::checkPlacement(int y, int x, Tile *tile)
{
  bool check = false;
  int trackR = 0;
  int trackL = 0;
  int trackU = 0;
  int trackD = 0;
  bool empty = true;

  for (int i = 0; i < 27; i++)
  {
    for (int l = 0; l < 27; l++)
    {

      if (board[i][l] != nullptr)
      {
        empty = false;
      }
    }
  }
  if (empty)
  { 
    
    return true;
  }
  /*  The for loop simutaneously tracks the rows and coloumns from the positions of the placed
  tile.
   if the length is obtained during the loop in any direction is greater than 5 the tile cannot be placed
   hence false is returned; (we include 6 in the if statement because we must count the tile placed as well in the chain);
   (similiar logic to the allocate points method)

  */

  for (int j = 1; j < 8; j++)
  {

    if (board[y][x - j] == nullptr && trackL == 0)
    {
      trackL = j - 1;
    }
    else if (board[y][x - j] != nullptr && (board[y][x - j]->getTileDets() == tile->getTileDets()))
    {
      return false;
    }

    if (board[y][x + j] == nullptr && trackR == 0)
    {
      trackR = j - 1;
    }
    else if (board[y][x + j] != nullptr && (board[y][x + j]->getTileDets() == tile->getTileDets()))
    {
      return false;
    }

    if (board[y + j][x] == nullptr && trackU == 0)
    {
      trackU = j - 1;
    }
    else if (board[y + j][x] != nullptr && (board[y + j][x]->getTileDets() == tile->getTileDets()))
    {
      return false;
    }

    if (board[y - j][x] == nullptr && trackD == 0)
    {
      trackD = j - 1;
    }
    else if (board[y - j][x] != nullptr && (board[y - j][x]->getTileDets() == tile->getTileDets()))
    {
      return false;
    }
  }
  if ((trackD + trackU) > 6 || (trackL + trackR) > 6)
  {
    return false;
  }
  else
    check = true;


  Tile *surrounding[8] =
      {board[y][x - 1], board[y][x - 2], board[y][x + 1], board[y][x + 2], board[y + 1][x], board[y + 2][x], board[y - 1][x], board[y - 2][x]};
//1st block to the left, 2nd to the left, 1st to the right, 2nd block on the right, 1st block on the top, 2nd block the top, 1st block on the bottom, 2nd block on the bottom
  // the surroundings of the block are placed inside a
  int shapeOrColour = 0;
  int shapeOrColour2 = 0;

  int counter = 0;
  bool valid = false;

  /*
    **PSEUDO**
    -Iterate the through the surroudings array, using the 1st and the 4th block as our basis for comparison
    -  As we iterate we compare the the 1st block to the left,
      if (1st block is null){
      move on to the other side
    } else { hold the trend of the left side and compare with the other}

    - If (conditions are met) {
      we can move on to the next check the verticals;
    }

    - Since we use on the 1st and 4th elements in the surroudings array iterate the counter by 4.
    -  Using the 4th element in the surroundings array, we can filter to the to see if the verticals are valid
    - If all is valid, valid is returned as true, else a false is returned to the placement method.
  */
  while (counter < 5)
  { //checking if the 1st or 4th block is null
    if (surrounding[counter] != nullptr)
    {
      Colour surColour = surrounding[counter]->getColour();
      Shape surShape = surrounding[counter]->getShape();
      if (surrounding[counter + 1] != nullptr) {

       if ( surColour == surrounding[counter + 1]->getColour())
      {
        if (surrounding[counter + 2] == nullptr)
        { if (counter == 0) {
          shapeOrColour = 1;
          } else if (counter == 4) {
          shapeOrColour2 = 1;
          }
        }
        else if (surrounding[counter + 2]->getColour() == surColour && surrounding[counter + 3]->getColour() == surColour)
        {
          if (counter == 0) {
          shapeOrColour = 1;
          } else if (counter == 4) {
          shapeOrColour2 = 1;
          }
        }
      }
      else if (surShape == surrounding[counter + 1]->getShape() )
      {
        if (surrounding[counter + 2] == nullptr)
        {
          if (counter == 0) {
          shapeOrColour = 2;
          } else if (counter == 4) {
          shapeOrColour2 = 2;
          }
        }
        else if (surrounding[counter + 2]->getShape() == surShape)
        {
          if (counter == 0) {
          shapeOrColour = 2;
          } else if (counter == 4) {
          shapeOrColour2 = 2;
          }
        }
      }
      }
      if (surrounding[counter + 1] == nullptr && surrounding[counter + 2] != nullptr)
      {
        if ((surrounding[counter + 2]->getShape() == surShape) && (surrounding[counter + 3]->getShape() == surShape))
        {
         if (counter == 0) {
          shapeOrColour = 2;
          } else if (counter == 4) {
          shapeOrColour2 = 2;
          }
        }
        else if ((surrounding[counter + 2]->getColour() == surColour) && (surrounding[counter + 3]->getColour() == surColour))
        {
          if (counter == 0) {
          shapeOrColour = 1;
          } else if (counter == 4) {
          shapeOrColour2 = 1;
          }
        }
      }
    }
    /*we must check whether the tile on the opposite sides are valid
       - and then check the continual block next to it to find whether the pattern is consistent on both sides (left right)/(up down)
     */
    else if (surrounding[counter + 2] == nullptr)
    {
      if (counter == 0) {
          shapeOrColour = 0;
          } else if (counter == 4) {
          shapeOrColour2 = 0;
       }
    }
    else if (surrounding[counter + 3] != nullptr)
    {
      if (surrounding[counter + 2]->getShape() == surrounding[counter + 3]->getShape())
      {
          if (counter == 0) {
          shapeOrColour = 2;
          } else if (counter == 4) {
          shapeOrColour2 = 2;
          }
      }
      else if (surrounding[counter + 2]->getColour() == surrounding[counter + 3]->getColour())
      {
          if (counter == 0) {
          shapeOrColour = 1;
          } else if (counter == 4) {
          shapeOrColour2 = 1;
          }
      }
    } else {
          if (counter == 0) {
          shapeOrColour = 0;
          } else if (counter == 4) {
          shapeOrColour2 = 0;
          }
    }
    counter += 4;
  }
  if(shapeOrColour == shapeOrColour2) {
    valid = true;
  } else if ((shapeOrColour == 0) || (shapeOrColour2 == 0)){

    if(surrounding[0] != nullptr || surrounding[2] != nullptr) {
        if(shapeOrColour == 1 )
        {
          if (tile->getColour() == surrounding[0]->getColour() || tile->getColour() == surrounding[2]->getShape()) {
            valid = true;
           }
        }
        if (shapeOrColour == 2)
        {
        if (tile->getShape() == surrounding[0]->getShape() || tile->getShape() == surrounding[2]->getShape())
        {
        valid = true;
        }
        }
         if(shapeOrColour2 == 1 )
        {
          if (tile->getColour() == surrounding[4]->getColour() || tile->getColour() == surrounding[6]->getShape()) {
            valid = true;
           }
        }
        if (shapeOrColour2 == 2)
        {
           if (tile->getShape() == surrounding[4]->getShape() || tile->getShape() == surrounding[6]->getShape())
            {
             valid = true;
            }
        }
    }
  } else valid = false;

 // a comparison to see whether the spot has been taken, if it has you cannot place a tile there.
  if (board[y][x] != nullptr)
  {
    return false;
  }
 /* Because we check the horizontals first,
    we need to save a boolean to check tell if the horizontal row is emtpy,
    if the vertical is not empty it can still place.
 */
  return valid;
}

//A boolean function to check if any of the player's hands are empty, to which it will end the game and check the score
bool QwirkleGame::gameFinished()
{
//This function game finished is a condition set in the while loop
  bool playerHandEmpty = false;

  for (int i = 0; i < players.size(); i++)
  {
    if (players[i]->getHand()->returnSize() == 0)
    {
      players[i]->setScore(6);
      playerHandEmpty = true;
    }
  }

  if (bag->getSize() == 0 && playerHandEmpty)
  {
    return true;
  }

  return false;
}

/*sets the position of the board to the tile meant to be placed*/

void QwirkleGame::setBoard(int x, int y, Tile *tile)
{
  board[y][x] = tile;
}

//Sets the current player of the turn
void QwirkleGame::setCurrentPlayer(Player *player)
{
  currentP = player;
}
Player *QwirkleGame::getCurrentPlayer()
{
  return currentP;
}
