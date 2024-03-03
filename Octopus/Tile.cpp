#include "Tile.h"
MyTile::MyTile(int x, int y)
{
	Texture = NULL;
	pos_x = x;
	pos_y = y;
	Width = 0;
	Height = 0;
	type = 0;
}
MyTile::~MyTile()
{
	free();
}