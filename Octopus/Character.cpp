#include "Character.h"
//MyCharacter
MyCharacter::MyCharacter(int x, int y)
{
	Texture = NULL;
	pos_x = x;
	pos_y = y;
	Width = 0;
	Height = 0;
	type = 0;
	isOnGround = 0;
}
MyCharacter::~MyCharacter()
{
	free();
}
bool MyCharacter::Check(MyTexture** layer,int x,int y)
{
	int j = (pos_x + x) / 16 ;
	int i = (pos_y + y) / 16 + 1;
	//std::cout << i << ' ' << j << '\n' << layer[i][j].getType()<<'\n';
	if (layer[i][j].getType() != -1)
	{
		
		return true;
	}
	return false;
}
void MyCharacter::Update(MyTexture** layer, SDL_Event& e,std::vector<SDL_Point> a, int& bgFrame)
{
	//std::cout << a[bgFrame] << '\n';
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			pos_y += WalkUp;
			if (Check(layer, 0, 0) == false)
			{
				pos_y -= WalkUp;
			}
			//pos_x += 10;
			break;
		case SDLK_LEFT:
			pos_x += WalkLeft;
			if (Check(layer, 0, 0) == false)
			{
				pos_x -= WalkLeft;
			}
			break;
		case SDLK_RIGHT:
			pos_x += WalkRight;
			if (Check(layer, 0, 0) == false)
			{
				pos_x -= WalkRight;
			}
			break;
		case SDLK_DOWN:
			pos_y += WalkDown;
			if (Check(layer, 0, 0) == false)
			{
				pos_y -= WalkDown;
			}
			break;
		//case SDLK_1:
		//	if (want_to_move == 1)
		//	{
		//		power -= 1;
		//		bgFrame += 1;
		//		pos_x = 86 * 4 - 43 - 16;pos_y = 30;
		//		//pos_y = SCREEN_HEIGHT - (a[bgFrame] + 2) * 36 -2;
		//		want_to_move = 2;
		//		isOnGround = false;
		//	}
		//	break;
		//case SDLK_2:
		//	if (want_to_move == 1)
		//	{
		//		power -= 2;
		//		bgFrame += 2;
		//		pos_x = 86 * 4 - 43 - 16;pos_y = 30;
		//		//pos_y = SCREEN_HEIGHT - (a[bgFrame] + 2)* 36 - 2;
		//		want_to_move = 2; 
		//	}
		//	break;
		//case SDLK_3:
		//	if (want_to_move == 1)
		//	{
		//		power -= 3;
		//		bgFrame += 3;
		//		pos_x = 86 * 4 - 43 - 16;pos_y = 30;
		//		//pos_y = SCREEN_HEIGHT - (a[bgFrame] + 2) * 36 - 2;
		//		want_to_move = 2; 
		//	}	
		//	break;
		//case SDLK_l:
		//	want_to_move = 1;
		//	break;
		}
	}
}
//void MyCharacter::Check(MyTexture** layer,int w,int h, int& bgFrame)
//{
//	PutOnGround(layer, w, h, bgFrame);
//	if (isOnGround != true)
//	{
//		pos_y += WalkDown;
//		PutOnGround(layer,w,h, bgFrame);
//		//if(pos_x != 0)pos_x += 2;
//	}
//
//
//}
//void MyCharacter::PutOnGround(MyTexture** Layer, int w_m, int& bgFrame,int w,int h)
//{
//	
//	if(isOnGround != true)
//	{
//		pos_y += 9;
//		int rt = pos_y / h, rb = (pos_y + 32 + 2) / h, ct = pos_x / w, cb = (pos_x + 32) / w;
//		ct = (ct + bgFrame) % w_m;
//		cb = (cb + bgFrame) % w_m;
//		if (Layer[rb][cb].getType() == 36 )
//		{
//			pos_y = (rb ) * h - 32;
//			isOnGround = true;
//		}
//		else if (Layer[rb][ct].getType() == 36)
//		{
//			pos_y = (rb ) * h - 32;
//			isOnGround = true;
//		}
//		else if (Layer[rb][cb].getType() == 37 || Layer[rb][ct].getType() == 37)
//		{
//			pos_x = 86 * 4 - 32 - 1;
//			pos_y = 0;
//			bgFrame = 0;
//			heart--;
//			isOnGround = false;
//			want_to_move = 0;
//		}
//		else
//		{
//			isOnGround = false;
//		}
//	}
//	else
//	{
//		int rt = pos_y / h, rb = (pos_y + 32 + 2) / h, ct = pos_x / w, cb = (pos_x + 32) / w;
//		if (Layer[rb][cb].getType() != 36)
//		{
//			
//			isOnGround = false;
//		}
//		else if (Layer[rb][ct].getType() != 36)
//		{
//			isOnGround = false;
//		}
//	}
//	if (isOnGround == true && want_to_move == 2)
//	{
//		want_to_move = 0;
//	}
//	if (pos_y < 0)pos_y = 0;
//	if (pos_x < 0)pos_x = 0;
//	if (pos_x > SCREEN_WIDTH - 72)pos_x = SCREEN_WIDTH - 72;
//	//if (pos_y > SCREEN_HEIGHT - 32)pos_y = SCREEN_HEIGHT - 72;
//	if (pos_x + 32 >= 86 * 4)pos_x = 86 * 4 - 32 - 1;
//	//return false;
//}