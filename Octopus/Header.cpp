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
	Path[1] = "";
	Path[0] = "";
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
void MyTexture::TShow(int x, int y, SDL_Rect* clip)
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
	SDL_RenderCopy(Renderer, Texture, clip, &newRect);
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
		Texture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
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
SDL_Texture* loadTexture(std::string path)
{

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else if (Renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}
//MyTile
MyTile::MyTile(int x, int y)
{
	Texture = NULL;
	pos_x = x;
	pos_y = y;
	Width = 0;
	Height = 0;
	type = 0;
	Path[1] = "";
	Path[0] = "";
}
MyTile::~MyTile()
{
	free();
}

//MyCharacter
MyCharacter::MyCharacter(int x, int y)
{
	Texture = NULL;
	pos_x = x;
	pos_y = y;
	Width = 0;
	Height = 0;
	type = 0;
	Path[1] = "";
	Path[0] = "";
}
MyCharacter::~MyCharacter()
{
	free();
}
bool MyCharacter::Update(SDL_Event& e)
{
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
		case SDLK_DOWN:
			pos_y += WalkDown;
			break;
		case SDLK_LEFT:
			pos_x += WalkLeft;
			break;
		case SDLK_RIGHT:
			pos_x += WalkRight;
			break;
		case SDLK_a:
			pos_x += WalkLeft;
			break;
		case SDLK_d:
			pos_x += WalkRight;
			break;
		case SDLK_w:
			if (isOnGround == true) pos_y += WalkUp, isOnGround = false;
			break;
		case SDLK_s:
			pos_y += WalkDown;
			break;
		case SDLK_l:
			pos_x += WalkRight1;
			break;

		}
		//if (pos_x  > SCREEN_WIDTH / 2)
		//{
		//	//std::cout << pos_x << '\n';	
		//	pos_x = 600;
		//	return false;
		//}
	}
	return true;
}
void MyCharacter::Check()
{
	PutOnGround();
	if (isOnGround != true)
	{
		pos_y += WalkDown;
		PutOnGround();
		//if(pos_x != 0)pos_x += 2;
	}
	if (pos_y < 0)pos_y = 0;
	if (pos_x < 0)pos_x = 0;
	if (pos_x > SCREEN_WIDTH - 72)pos_x = SCREEN_WIDTH - 72;
	if (pos_y > SCREEN_HEIGHT - 72)pos_y = SCREEN_HEIGHT - 72;
	if (pos_x >= 150)pos_x = 150;

}
void MyCharacter::PutOnGround()
{
	int rt = pos_y / 18, rb = (pos_y + 30) / 18, ct = pos_x / 18, cb = (pos_x + 33) / 18;
	ct = (ct + bgFrame) % M_W_2;
	cb = (cb + bgFrame) % M_W_2;
	/*if (Layer3[rt][ct].getType() == 1 || Layer3[rt][ct].getType() == 2 || Layer3[rt][ct].getType() == 3)
	{
		pos_y = (rt - 1) * 18 - 1;
		isOnGround = true;
	}
	else*/
	if (Layer3[rb][cb].getType() == 1 || Layer3[rb][cb].getType() == 2 || Layer3[rb][cb].getType() == 3)
	{
		pos_y = (rb) * 18 - 30 - 1;
		isOnGround = true;
	}
	else if (Layer3[rb][ct].getType() == 1 || Layer3[rb][ct].getType() == 2 || Layer3[rb][ct].getType() == 3)
	{
		pos_y = (rb) * 18 - 30 - 1;
		isOnGround = true;
	}
	else if (Layer3[rb][cb].getType() == 68 || Layer3[rb][ct].getType() == 68)
	{
		pos_x = 0;
		pos_y = 0;
		bgFrame = 0;
		heart--;
	}
	else if (Layer2[rb][cb].getType() == 68 || Layer2[rb][ct].getType() == 68)
	{
		pos_x = 0;
		pos_y = 0;
		bgFrame = 0;
		heart--;
	}
	else
	{
		isOnGround = false;
	}
	//return false;
}


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
	Path[1] = "";
	Path[0] = "";
	cnt = 0;
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
	if (ck)cnt ^= 1;
	else if (cnt == 1)cnt ^= 1;
	loadFromFile(Path[cnt]);
	return ck;

}
void MyButton::givePath(std::string path1, std::string path2)
{
	Path[1] = path1;
	Path[0] = path2;
}

//MyText
MyText::MyText(int x, int y)
{
	//Initialize
	Texture = NULL;
	pos_x = x;
	pos_y = y;
	Width = 0;
	Height = 0;
	type = 0;
	Path[1] = "";
	Path[0] = "";
}
MyText::~MyText()
{
	free();
}
bool MyText::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		Texture = SDL_CreateTextureFromSurface(Renderer, textSurface);
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