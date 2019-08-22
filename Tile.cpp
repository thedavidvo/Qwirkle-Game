
#include "Tile.h"

Tile::Tile(Colour colour, Shape shape)
{
  this->colour = colour;
  this->shape = shape;
}

Colour Tile::getColour()
{
  return this->colour;
}

Shape Tile::getShape()
{
  return this->shape;
}

std::string Tile::getTileDets(){

std::string details = colour + std::to_string(shape);

return details;
}


void Tile::printTile()
{
  // double f = shape;
 std::cout << colour << shape;
 
}
