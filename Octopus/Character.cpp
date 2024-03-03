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
void MyCharacter::Update(SDL_Event& e,int a[], int& bgFrame)
{
	std::cout << a[bgFrame] << '\n';
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			if (isOnGround == true)
			{
				pos_y += WalkUp;
				isOnGround = false;
			}
			//pos_x += 10;
			break;
		case SDLK_LEFT:
			pos_x += WalkLeft;
			break;
		case SDLK_RIGHT:
			pos_x += WalkRight;
			break;
		case SDLK_1:
			if (want_to_move == true)
			{
				bgFrame += 1;
				pos_x = 86 * 3 - 43 - 16;pos_y = 30;
				//pos_y = SCREEN_HEIGHT - (a[bgFrame] + 2) * 36 -2;
				
			}
			break;
		case SDLK_2:
			if (want_to_move == true)
			{
				bgFrame += 2;
				pos_x = 86 * 3 - 43 - 16;pos_y = 30;
				//pos_y = SCREEN_HEIGHT - (a[bgFrame] + 2)* 36 - 2;
			
			}
			break;
		case SDLK_3:
			if (want_to_move == true)
			{
				bgFrame += 3;
				pos_x = 86 * 3 - 43 - 16;pos_y = 30;
				//pos_y = SCREEN_HEIGHT - (a[bgFrame] + 2) * 36 - 2;
				
			}	
			break;
		case SDLK_l:
			want_to_move = true;
			break;
		}
		std::cout << SCREEN_HEIGHT - (a[bgFrame] + 2) * 36 - 2 << '\n';
		//if (pos_x  > SCREEN_WIDTH / 2)
		//{
		//	//std::cout << pos_x << '\n';	
		//	pos_x = 600;
		//	return false;
		//}
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
void MyCharacter::PutOnGround(MyTexture** Layer, int w_m, int& bgFrame,int w,int h)
{
	
	if(isOnGround != true)
	{
		pos_y += 9;
		int rt = pos_y / h, rb = (pos_y + 32 + 2) / h, ct = pos_x / w, cb = (pos_x + 32) / w;
		ct = (ct + bgFrame) % w_m;
		cb = (cb + bgFrame) % w_m;
		//std::cout << bgFrame << '\n';
		//std::cout << rt << ' ' << rb << ' ' << ct << ' ' << cb << '\n';
		/*if (Layer3[rt][ct].getType() == 1 || Layer3[rt][ct].getType() == 2 || Layer3[rt][ct].getType() == 3)
		{
			pos_y = (rt - 1) * 18 - 1;
			isOnGround = true;
		}
		else*/
		//std::cout << 
		if (Layer[rb][cb].getType() == 36 )
		{
			pos_y = (rb ) * h - 32;
			isOnGround = true;
		}
		else if (Layer[rb][ct].getType() == 36)
		{
			pos_y = (rb ) * h - 32;
			isOnGround = true;
		}
		else if (Layer[rb][cb].getType() == 37 || Layer[rb][ct].getType() == 37)
		{
			pos_x = 10;
			pos_y = 0;
			bgFrame = 0;
			heart--;
			isOnGround = false;
		}
		else
		{
			isOnGround = false;
		}
	}
	else
	{
		int rt = pos_y / h, rb = (pos_y + 32 + 2) / h, ct = pos_x / w, cb = (pos_x + 32) / w;
		if (Layer[rb][cb].getType() != 36)
		{
			
			isOnGround = false;
		}
		else if (Layer[rb][ct].getType() != 36)
		{
			isOnGround = false;
		}
	}
	if (pos_y < 0)pos_y = 0;
	if (pos_x < 0)pos_x = 0;
	if (pos_x > SCREEN_WIDTH - 72)pos_x = SCREEN_WIDTH - 72;
	//if (pos_y > SCREEN_HEIGHT - 32)pos_y = SCREEN_HEIGHT - 72;
	if (pos_x + 32 >= 86 * 4)pos_x = 86 * 4 - 32 - 1;
	//return false;
}