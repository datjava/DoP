#pragma once
#include "Header.h"
#include "Text.h"
//static MyTexture** Layer1 = NULL, ** Layer2 = NULL, ** Layer3 = NULL;
class MyCharacter : public MyTexture
{
public:
	MyCharacter(int x = 0, int y = 0);
	~MyCharacter();
	void Update(MyTexture** layer,double x,double y);
	int Check(MyTexture** layer);
	int getX(){ return pos_x; }
	int getY() { return pos_y; }
	void changePower(int x) { power = x; }	
	int getPower() { return power; }
private:
	int power = 0;
};