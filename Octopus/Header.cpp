#include "Header.h"
//MyTexture
MyTexture::MyTexture(int x, int y)
{
	Texture = NULL;
	pos_x = x;
	pos_y = y;
	Width = 0;
	Height = 0;
	type = 0;
	renderer = NULL;
}
MyTexture::~MyTexture()

{
	//Deallocate
	free();
}
void MyTexture::free()
{
	if (Texture != NULL)
	{
		SDL_DestroyTexture(Texture);
		Texture = NULL;
		pos_x = 0;
		pos_y = 0;
		Width = 0;
		Height = 0;
		type = 0;
	}
}
void MyTexture::setRenderer(SDL_Renderer* _renderer)
{
	renderer = _renderer;
}
void MyTexture::TShow( double x, double y, SDL_Rect* clip)
{
	//free();
	if (x != -1 && y != -1)
	{

		pos_x = x;
		pos_y = y;
	}
	else
	{
		x = pos_x;
		y = pos_y;
	}
	SDL_Rect newRect = { x,y,Width,Height };
	if (clip != NULL)
	{
		newRect.w = clip->w;
		newRect.h = clip->h;
	}
	//render new texture to screen
	SDL_RenderCopy(renderer, Texture, clip, &newRect);
}
int MyTexture::getHeight()
{
	return Height;
}
int MyTexture::getWidth()
{
	return Width;
}
void MyTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(Texture, alpha);
}
bool MyTexture::loadFromFile(std::string path, int value)
{
	free();
	if (value == -1)
	{
		type = -1;
		return true;
	}
	bool success = true;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());//load image
	//SDL_Renderer* Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (loadedSurface == NULL)
	{
		printf("Could not load image\n");
		success = false;
	}
	else
	{
		Texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if(renderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		}
		if (Texture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			////SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
			//Get image dimensions
			Width = loadedSurface->w;
			Height = loadedSurface->h;
			type = value;
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	//Texture = loadTexture(path.c_str());
	return  Texture != NULL;
}

//SDL_Texture* loadTexture(std::string path)
//{
//
//	//The final texture
//	SDL_Texture* newTexture = NULL;
//
//	//Load image at specified path
//	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//	if (loadedSurface == NULL)
//	{
//		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
//	}
//	else if ()
//	{
//		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
//	}
//	else
//	{
//		//Create texture from surface pixels
//		newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
//		if (newTexture == NULL)
//		{
//			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
//		}
//
//		//Get rid of old loaded surface
//		SDL_FreeSurface(loadedSurface);
//	}
//
//	return newTexture;
//}
//MyTile

