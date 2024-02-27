//Using SDL and standard IO
#include "Header.h"
#include "generate_map.h"
bool init();
bool MediaLoad();
bool init();
void close();
SDL_Window* window = NULL;
SDL_Renderer* Renderer = NULL;
SDL_Event e;


int main(int argc, char* args[])
{


	if (init() == 0)
	{
		printf("SDL could not initialize \n");
	}
	else if (MediaLoad() == 0)
	{
		printf("Failed to load media\n");
	}
	else
	{
		bool quit = false;
		SDL_Event e;
		int CharFrame = 0;
		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					for (int i = 0; i < TOTAL_BUTTONS; ++i)
					{
						if (Button[i].handleEvent(e) == true)
						{
							switch (i)
							{
							case play_:
								bg_ = MAIN;
								break;
							case quit_:
								quit = true;
								break;
							case settings_:
								bg_ = SETTING_CHAR;
								break;
							case back_:
								switch (bg_)
								{
								case SETTING_CHAR:
									bg_ = MENU;
									break;
								case SETTING_MAP:
									bg_ = SETTING_CHAR;
									break;
								case MAIN:
									bg_ = MENU;
									break;
								}
								break;
							case char_1:
								//bg_ = 3;
								//Char.loadFromFile("image/jelly1.png");
								break;
							case char_2:
								//Char.loadFromFile("image/jelly2.png");
								break;
							case char_3:
								//Char.loadFromFile("image/jelly3.png");
								//bg_ = 5;
								break;
							case map_1:
								//bg_ = SETTING;
								MapType = '1';
								CreateMap("image/map.txt", Layer1, M_H_1, M_W_1, MapType);
								CreateMap("image/layer2.txt", Layer2, M_H_2, M_W_2, MapType);
								CreateMap("image/layer3.txt", Layer3, M_H_2, M_W_2, MapType);
								break;
							case map_2:
								//bg_ = SETTING;
								MapType = '2';
								CreateMap("image/map.txt", Layer1, M_H_1, M_W_1, MapType);
								CreateMap("image/layer2.txt", Layer2, M_H_2, M_W_2, MapType);
								CreateMap("image/layer3.txt", Layer3, M_H_2, M_W_2, MapType);
								break;
							case confirm_:
								bg_++;
								break;
							}
						}
					}
				}
				else if (e.type == SDL_KEYDOWN)
				{
					Char.Update(e);
					switch (e.key.keysym.sym)
					{
					case (SDLK_LEFT):
						bgFrame -= dis;
						//CharFrame++;
						break;
					case (SDLK_RIGHT):
						bgFrame += dis_l;
						//CharFrame++;
						break;
					case (SDLK_a):
						bgFrame -= dis;
						//CharFrame++;

						break;
					case (SDLK_d):
						bgFrame += dis;
						//CharFrame++;
						break;
					case (SDLK_l):
						//CharFrame++;
						bgFrame += dis_l;
						break;
					}
					//CharFrame++;

				}
				else if (e.type == SDL_KEYUP)
				{
					CharFrame = 0;
				}

			}

			SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
			SDL_RenderClear(Renderer);
			bg_ = std::max(0, bg_);
			bg_ %= TOTAL_SCREEN_;
			BackgroundTexture[bg_].TShow(0, 0);
			if (bg_ == MENU)
			{
				Button[play_].TShow(200, 350);
				Button[quit_].TShow(200, 490);
				Button[settings_].TShow(200, 420);
				
			}
			else if (bg_ == SETTING_CHAR)
			{
				Button[back_].TShow(20, 570);
				Button[char_1].TShow(330, 300);
				Button[char_2].TShow(530, 300);
				Button[char_3].TShow(730, 300);
				Button[confirm_].TShow(1030, 570);
			}
			else if (bg_ == SETTING_MAP)
			{
				Button[back_].TShow(20, 570);
				SDL_Rect clip = { 0,0,180,180 };
				Button[map_1].TShow(400, 300, &clip);
				Button[map_2].TShow(630, 300, &clip);
				Button[confirm_].TShow(1030, 570);
			}
			else if (bg_ == MAIN)
			{
				
				bgFrame = std::max(0, bgFrame);
				for (int i = 0; i < M_H_1; ++i)
				{
					for (int k = bgFrame; k < bgFrame + M_W_1; ++k)
					{
						int j = k % M_W_1;
						if (Layer1[i][j].getType() != -1)
						{
							Layer1[i][j].TShow((k - bgFrame) * TILE_LY1, i * TILE_LY1);
						}
					}
				}
				for (int i = 0; i < M_H_2; ++i)
				{
					for (int k = bgFrame; k < bgFrame + M_W_2; ++k)
					{
						int j = k % M_W_2;
						if (Layer2[i][j].getType() != -1)
						{
							Layer2[i][j].TShow((k - bgFrame) * TILE_LY2, i * TILE_LY2);
						}
					}
				}
				for (int i = 0; i < M_H_2; ++i)
				{
					for (int k = bgFrame; k < bgFrame + M_W_2; ++k)
					{
						int j = k % M_W_2;
						if (Layer3[i][j].getType() != -1)
						{
							Layer3[i][j].TShow((k - bgFrame) * TILE_LY2, i * TILE_LY2);
						}
					}
				}
				//CharFrame = std::max(0, CharFrame);
				CharFrame++;
				CharFrame %= 4;
				Button[back_].TShow(20, 570);
				Char.Check();
				Char.TShow(-1, -1, &Clip[CharFrame]);
				//show heart and power
				for (int i = 0; i < Char.totalHeart(); ++i)
				{
					Heart.TShow(10 + i * 36, 10);
				}
				for (int i = 0; i < cur_power; ++i)
				{
					if (i < Char.totalPower())
					{
						if (i == 0)
							Pow[1][0].TShow(10 + i * 9, 40);
						else if (i < Char.totalPower() - 1)
							Pow[1][1].TShow(10 + i * 9, 40);
						else
							Pow[1][2].TShow(10 + i * 9, 40);
					}
					else
					{
						if (i == Char.totalPower() - 1)
							Pow[0][2].TShow(10 + i * 9, 40);
						else
							Pow[0][2].TShow(10 + i * 9, 40);
					}
				}
				if (Char.totalHeart() == 0)
				{
					Char.~MyCharacter();
					if (Text.loadFromRenderedText("Game over", { 213,158,74 }))
					{
						Text.TShow(SCREEN_WIDTH / 2 - Text.getWidth() / 2, SCREEN_HEIGHT / 2 - Text.getHeight() / 2);
					}
					else
					{
						printf("Failed to render text texture!\n");
					}
				}
				SDL_Delay(50);
			
			}
			//Button[level_1].TShow(200, 420);

			SDL_RenderPresent(Renderer);


		}


	}
	close();
	return 0;
}


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: \n");
			success = false;
		}
		else
		{
			//Get window surface
			//ScreenSurface = SDL_GetWindowSurface(window);
			Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (Renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}

		}

	}
	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		success = false;
	}
	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	return success;
}
bool MediaLoad()
{
	bool success = true;
	int n, m;
	std::ifstream fin("side.txt");
	if (!fin.is_open())
	{
		std::cout << "Can't open file SIDE.txt";
		success = false;
	}
	else
	{
		fin >> n >> m;
		generate_layer2(n, m);
		fin >> n >> m;
		int** map = new int* [n + 1];
		for (int i = 0; i <= n; ++i)
		{
			map[i] = new int[m + 1];
		}
		generate_layer3(n, m, map);

		fin >> n >> m;
		generate_map(n, m);

	}
	//load background texture
	if (BackgroundTexture[MENU].loadFromFile("image/Menu.png") == 0)
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}
	if (BackgroundTexture[SETTING_CHAR].loadFromFile("image/SETTING_CHAR.png") == 0)
	{
		printf("Failed to load background texture image!\n");
		success = false;

	}
	if (BackgroundTexture[SETTING_MAP].loadFromFile("image/MAP.png") == 0)
	{
		printf("Failed to load background texture image!\n");
		success = false;

	}
	
	//load character texture
	if (Char.loadFromFile("image/Capture1_!.png") == 0)
	{
		printf("Failed to load character texture image!\n");
		success = false;
	}
	for (int i = 0; i < TOTAL_BUTTONS; ++i)
	{
		std::string s1 = "image/", s2 = "image/";
		switch (i)
		{
		case play_:
			s1 += "play1.png";
			s2 += "play2.png";
			break;
		case quit_:
			s1 += "quit1.png";
			s2 += "quit2.png";
			break;
		case settings_:
			s1 += "setting1.png";
			s2 += "setting2.png";
			break;
		case back_:
			s1 += "back1.png";
			s2 += "back1.png";
			break;
		case map_1:
			s1 += "map11.png";
			s2 += "map12.png";
			break;
		case map_2:
			s1 += "map21.png";
			s2 += "map22.png";
			break;
		case confirm_:
			s1 += "confirm1.png";
			s2 += "confirm1.png";
			break;
		case char_1:
			s1 += "jel1.png";
			s2 += "jel11.png";
			break;
		case char_2:
			s1 += "jel2.png";
			s2 += "jel21.png";
			break;
		case char_3:
			s1 += "jel3.png";
			s2 += "jel31.png";
			break;

		}
		Button[i].givePath(s2, s1);
		if (Button[i].loadFromFile(s2) == 0 || Button[i].loadFromFile(s1) == 0)
		{

			printf("Failed to load button texture image!\n");
			success = false;
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		Clip[i].x = i * 30;
		Clip[i].y = 0;
		Clip[i].w = 30;
		Clip[i].h = 33;
	}
	//Load tile texture
	Layer1 = new MyTexture * [M_H_1];
	for (int i = 0; i <= M_H_1; ++i)
	{
		Layer1[i] = new MyTexture[M_W_1];
	}
	Layer2 = new MyTexture * [M_H_2];
	for (int i = 0; i <= M_H_2; ++i)
	{
		Layer2[i] = new MyTexture[M_W_2];
	}
	Layer3 = new MyTexture * [M_H_2];
	for (int i = 0; i <= M_H_2; ++i)
	{
		Layer3[i] = new MyTexture[M_W_2];
	}
	CreateMap("image/map.txt", Layer1, M_H_1, M_W_1, MapType);
	CreateMap("image/layer2.txt", Layer2, M_H_2, M_W_2, MapType);
	CreateMap("image/layer3.txt", Layer3, M_H_2, M_W_2, MapType);
	//load heart and power
	if (Heart.loadFromFile("image/heart1.png") == 0)
	{
		printf("Failed to load heart texture image!\n");
		success = false;
	}
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			//"D:\lib\Octopus\image\tile_bg\pow\00.png"
			std::string s = "image/tile_bg/pow/";
			s += (char)(i + '0');
			s += (char)(j + '0');
			s += ".png";
			if (Pow[i][j].loadFromFile(s) == 0)
			{
				printf("Failed to load power texture image!\n");
				success = false;
			}
		}
	}
	if (gFont == NULL)
	{
		gFont = TTF_OpenFont("font/lazy.ttf", 72);
		if (gFont == NULL)
		{
			printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
			success = false;
		}
	}
	return success;

}
void CreateMap(const std::string& Path, MyTexture** Layer, int MAP_H, int MAP_W, char map_)
{
	std::ifstream fin(Path.c_str());
	if (fin.is_open())
	{
		for (int i = 0; i < MAP_H; ++i)
		{
			for (int j = 0; j < MAP_W; ++j)
			{
				int v;
				fin >> v;
				std::string value = std::to_string(v);
				//std::cout << value;
				std::string s = "image/tile_bg/map";
				s += map_;
				s += "/tile_";
				//std::cout << s << '\n';
				while (value.size() != 4)value = "0" + value;
				s += value;
				s += ".png";

				if (value != "0000")
				{
					if (Layer[i][j].loadFromFile(s, v) == 0)
					{
						std::cout << s << '\n';
						printf("Failed to load tile texture image!\n");
					}
					//std::cout << s << '\n';
				}
				else
				{
					Layer[i][j].loadFromFile(s, -1);
				}

			}
		}
	}
	else
	{
		printf("Failed to open map file!\n");
	}
}
void close()
{

	//Destroy window	
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	Renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
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