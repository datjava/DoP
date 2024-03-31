#pragma once
#include "Header.h"
//static MyTexture** Layer1 = NULL, ** Layer2 = NULL, ** Layer3 = NULL;
class MyCharacter : public MyTexture
{
public:
	MyCharacter(int x = 0, int y = 0);
	~MyCharacter();
	void Update(MyTexture** layer, SDL_Event& e,std::vector<SDL_Point> a, int& bgFrame);
	bool Check(MyTexture** layer,int x,int y);
	
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