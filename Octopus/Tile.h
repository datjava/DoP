#pragma once
#include "Header.h"
class MyTile : public MyTexture
{
public:
	MyTile(int x = 0, int y = 0);
	~MyTile();
	int getType() { return type; }
private:
	SDL_Point point;
};