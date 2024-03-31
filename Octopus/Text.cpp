#include "Text.h"

//MyText
MyText::MyText(int x,int y)
{
	//Initialize
	Texture = NULL;
	Width = 0;
	Height = 0;
	type = 0;
	if (x != -1 && y != -1)
	{
		pos_x = x;
		pos_y = y;
	}
	else
	{
		pos_x = 0;
		pos_y = 0;
	}
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		//success = false;
	}
}
MyText::~MyText()
{
	free();
}
bool MyText::loadFromRenderedText(std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(gFont, textureText.c_str(), textColor, 470);
	
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (Texture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			Width = textSurface->w;
			Height = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return Texture != NULL;
}
void MyText::setFont(int size, std::string tF)
{
	gFont = TTF_OpenFont(tF.c_str(), size);
}