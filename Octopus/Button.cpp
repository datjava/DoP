#include "Button.h"	
//MyButton
MyButton::MyButton(int x, int y)
{
	//Initialize
	Texture = NULL;
	pos_x = x;
	pos_y = y;
	Width = 0;
	Height = 0;
	type = 0;
}
MyButton::~MyButton()
{
	free();
}
bool MyButton::IsInside(int m_x, int m_y)
{
	if (m_x >= pos_x && m_x <= pos_x + Width && m_y >= pos_y && m_y <= pos_y + Height)
	{
		return true;
	}
	else return false;
}
bool MyButton::handleEvent(const SDL_Event& e)
{
	int m_x = 0, m_y = 0;
	m_x = e.button.x;
	m_y = e.button.y;
	bool ck = IsInside(m_x, m_y);
	return ck;

}

