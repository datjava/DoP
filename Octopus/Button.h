#pragma once
#include "Header.h"
class MyButton : public MyTexture
{
public:
	MyButton(int x = 0, int y = 0);
	~MyButton();
	bool handleEvent(const SDL_Event& e);
	bool IsInside(int m_x, int m_y);
};