
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>
#include "TileCodes.h"
#include <iostream>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:

Tile(Colour colour, Shape shape);

Colour getColour();
Shape getShape();
std::string getTileDets();

void printTile();

private:
   Colour colour;
   Shape  shape;
};

#endif // ASSIGN2_TILE_H
