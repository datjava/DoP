#pragma once
#include "Header.h"
class MyText : public MyTexture
{
public:
	MyText(int x = -1,int y = -1);
	~MyText();
	bool loadFromRenderedText( std::string textureText, SDL_Color textColor);
	void setFont(int size = 28, std::string tF = "font/lazy1.ttf");
private:

TTF_Font* gFont = NULL;
};
//static SDL_Event e;
//static SDL_Window* window = NULL;
//static SDL_Renderer* Renderer = NULL;
