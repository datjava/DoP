#pragma once
#include "Header.h"
class MyButton : public MyTexture
{
public:
	MyButton(int x = 0, int y = 0);
	~MyButton();
	bool handleEvent(const SDL_Event& e);
	bool IsInside(int m_x, int m_y);
	void givePath(std::string path1, std::string path2);
	int getCnt() { return cnt; }
private:
	int cnt = 0;
	std::string Path[2];
};