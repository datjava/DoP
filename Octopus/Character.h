#pragma once
#include "Header.h"
//static MyTexture** Layer1 = NULL, ** Layer2 = NULL, ** Layer3 = NULL;
class MyCharacter : public MyTexture
{
public:
	MyCharacter(int x = 0, int y = 0);
	~MyCharacter();
	void Update(SDL_Event& e,int a[], int& bgFrame);
	//void Check(MyTexture** layer, int w, int h, int& bgFrame);
	void PutOnGround(MyTexture** layer, int w_m,int& bgFrame,int w = TILE_LY2,int h = TILE_LY2);
	int getX(){ return pos_x; }
	int getY() { return pos_y; }
	int totalHeart() { return heart; }
	int totalPower() { return power; }
	int getState() { return want_to_move; }
private:
	bool isOnGround = 0;
	int heart = 3;
	int power = 16;
	int want_to_move = 0;
};