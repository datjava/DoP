#include "Play_game.h"
Game::Game()
{

	window = NULL;
	Renderer = NULL;
	Char = NULL;
	bg_ = MENU, alp = 255, dis = 1, dis_l = 1, cur_point = 0;
	cur_power = 16;
	bgFrame = 0;
	MapType = '1';
	Layer1 = NULL;
	Layer2 = NULL;
	arr = NULL;
	Gate = NULL;
}

Game::~Game()
{
	close();
}
bool Game::init()
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
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 4);
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
	return success;
}
bool Game::MediaLoad()
{
	bool success = true;
	//load map
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
		generate_layer2(n, m, arr);
		//std::cout << arr[0];

	}
	//load background texture
	for (int i = 0; i < TOTAL_SCREEN_; ++i)
		BackgroundTexture[i].setRenderer(Renderer);
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
	if (BackgroundTexture[GAME_OVER].loadFromFile("image/GAMEOVER.png") == 0)
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}
	if (BackgroundTexture[MAIN].loadFromFile("image/nature1/0.png") == 0)
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}
	//load character texture
	Char = new MyCharacter(86 * 3 + 10,0);
	Char->setRenderer(Renderer);
	if (Char->loadFromFile("image/Pink_Monster_Jump_8.png") == 0)
	{
		printf("Failed to load character texture image!\n");
		success = false;
	}
	//load button texture
	for (int i = 0; i < TOTAL_BUTTONS; ++i)
	{
		Button[i].setRenderer(Renderer);
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
			s1 += "map1_1.png";
			s2 += "map1_2.png";
			break;
		case map_2:
			s1 += "map2_1.png";
			s2 += "map2_2.png";
			break;

		case confirm_:
			s1 += "confirm1.png";
			s2 += "confirm1.png";
			break;
		case char_1:
			s1 += "Pink_Monster.png";
			s2 += "Pink_Monster.png";
			break;
		case char_2:
			s1 += "Dude_Monster.png";
			s2 += "Dude_Monster.png";
			break;
		case char_3:
			s1 += "Owlet_Monster.png";
			s2 += "Owlet_Monster.png";
			break;

		}
		Button[i].givePath(s2, s1);
		if (Button[i].loadFromFile(s2) == 0 || Button[i].loadFromFile(s1) == 0)
		{

			printf("Failed to load button texture image!\n");
			success = false;
		}
	}
	//load clip
	for (int i = 0; i < 8; ++i)
	{
		/*Clip[i].x = i * 30;
		Clip[i].y = 0;
		Clip[i].w = 30;
		Clip[i].h = 33;*/
		Clip[i].x = i * 32;
		Clip[i].y = 0;
		Clip[i].w = 32;
		Clip[i].h = 32;
	}
	for(int i = 0; i < 4; ++i)
		for (int j = 0; j < 8; ++j)
		{
			Clip_[i][j].x = j * 256;
			Clip_[i][j].y = i * 256;
			Clip_[i][j].w = 256;
			Clip_[i][j].h = 256;
		}
	//load main bg
	Layer1 = new MyTexture* [3];
	for (int i = 1; i <= 2; ++i)
	{
		Layer1[i] = new MyTexture[5];
		for (int j = 0; j < 5; ++j)
		{
			Layer1[i][j].setRenderer(Renderer);
			std::string path = "image//nature";
			path += (char)((i)+'0');
			path += "//";
			path += (char)(j + '0');
			path += ".png";
			std::cout << path << '\n';
			if (Layer1[i][j].loadFromFile(path) == 0)
				printf("Failed to load22 tile texture image!\n");
		}

	}
	//Load tile texture
	Layer2 = new MyTexture * [M_H_2];
	for (int i = 0; i < M_H_2; ++i)
	{
		Layer2[i] = new MyTexture[M_W_2];
	}
	//CreateMap("image/map.txt", Layer1, M_H_1, M_W_1, MapType);
	CreateMap("image/map.txt", Layer2, M_H_2, M_W_2, MapType);
	//load heart and power
	Heart.setRenderer(Renderer);
	if (Heart.loadFromFile("image/heart1.png") == 0)
	{
		printf("Failed to load heart texture image!\n");
		success = false;
	}
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			Pow[i][j].setRenderer(Renderer);
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
	//load text
	Text.setRenderer(Renderer);
	//load gate
	Gate = new MyTexture();
	Gate->setRenderer(Renderer);
	/*if (Gate->loadFromFile("image/Water9.png") == 0)
	{
		printf("Failed to load gate texture image!\n");
		success = false;
	}*/
	return success;

}
void Game::CreateMap(const std::string& Path, MyTexture** Layer, int MAP_H, int MAP_W, char map_)
{
	//map_ is type of map
	std::ifstream fin(Path.c_str());
	if (fin.is_open())
	{
		for (int i = 0; i < MAP_H; ++i)
		{
			for (int j = 0; j < MAP_W; ++j)
			{
				Layer[i][j].setRenderer(Renderer);
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
					//std::cout << s << '\n';
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
void Game::handleInput()
{
	//SDL_Event e;
	int CharFrame = 0;
	//bool quit = false;
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
							if (Char == NULL)
							{
								Char = new MyCharacter();
								Char->setRenderer(Renderer);
								MediaLoad();
							}
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
							case GAME_OVER:
								bg_ = MENU;
								break;
							}
							break;
						case char_1:
							//bg_ = 3;
							Char->loadFromFile("image/Pink_Monster_Jump_8.png");
							break;
						case char_3:
							Char->loadFromFile("image/Owlet_Monster_Jump_8.png");
							break;
						case char_2:
							Char->loadFromFile("image/Dude_Monster_Jump_8.png");
							//bg_ = 5;
							break;
						case map_1:
							//bg_ = SETTING;
							MapType = '1';
							map = 1;
							
							//CreateMap("image/map.txt", Layer1, M_H_1, M_W_1, MapType);
							CreateMap("image/map.txt", Layer2, M_H_2, M_W_2, MapType);
							//CreateMap("image/layer3.txt", Layer3, M_H_2, M_W_2, MapType);
							break;
						case map_2:
							//bg_ = SETTING;
							MapType = '2';
							map = 2;
							
							//CreateMap("image/map.txt", Layer1, M_H_1, M_W_1, MapType);
							CreateMap("image/map.txt", Layer2, M_H_2, M_W_2, MapType);
							//CreateMap("image/layer3.txt", Layer3, M_H_2, M_W_2, MapType);
							break;

						case confirm_:
							switch (bg_)
							{
							case SETTING_CHAR:
								bg_ = SETTING_MAP;
								break;
							case SETTING_MAP:
								bg_ = MAIN;
								break;


							default:
								break;
							}
							break;
						}
					}
				}
			}
			else if (e.type == SDL_KEYDOWN)
			{
				if (Char != NULL)Char->Update(e,arr,bgFrame);

				//switch (e.key.keysym.sym)
				//{
				////case (SDLK_LEFT):
				////	bgFrame -= dis;
				////	//CharFrame++;
				////	break;
				////case (SDLK_RIGHT):
				////	bgFrame += dis_l;
				////	//CharFrame++;
				////	break;
				////case (SDLK_a):
				////	bgFrame -= dis;
				////	//CharFrame++;

				////	break;
				////case (SDLK_d):
				////	bgFrame += dis;
				////	//CharFrame++;
				////	break;
				////case (SDLK_l):
				////	//CharFrame++;
				////	bgFrame += dis_l;
				////	break;
				//}
				CharFrame++;

			}
			else if (e.type == SDL_KEYUP)
			{
				CharFrame = 0;
			}

		}
		SDL_RenderClear(Renderer);
		SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		bg_ = std::max(0, bg_);
		bg_ %= TOTAL_SCREEN_;
		SDL_Rect clip = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
		BackgroundTexture[bg_].TShow(0, 0, &clip);
		//std::cout << bg_ << '\n';
		if (bg_ == MENU)
		{
			Button[play_].TShow(200, 350);
			Button[quit_].TShow(200, 490);
			Button[settings_].TShow(200, 420);

		}
		if (bg_ == SETTING_CHAR)
		{
			Button[back_].TShow(20, 570);
			Button[char_1].TShow(330, 300);
			Button[char_2].TShow(530, 300);
			Button[char_3].TShow(730, 300);
			Button[confirm_].TShow(1030, 570);
		}
		if (bg_ == SETTING_MAP)
		{
			Button[back_].TShow(20, 570);
			SDL_Rect clip = { 0,0,200,144 };
			Button[map_1].TShow(400, 300, &clip);
			Button[map_2].TShow(630, 300, &clip);
			Button[confirm_].TShow(1030, 570);
		}
		if (Char != NULL && bg_ == MAIN)
		{
			if (Char->totalHeart() <= 0)
			{
				Char = NULL;
				bg_ = GAME_OVER;
			}
			if (Char != NULL)
			{
				bgFrame = std::max(0, bgFrame);
				//show map
				SDL_Rect rect;
				rect.x = bgFrame / 1200;
				rect.y = 0;
				rect.w = SCREEN_WIDTH;
				rect.h = SCREEN_HEIGHT;
				Layer1[map][0].TShow(0, 0,&rect);		
				//std::cout <<bgFrame << '\n';			
				for (int i = 0;i < M_H_2;++i)
				{
					for (int j = bgFrame; j <M_W_2; ++j)
					{
						if (Layer2[i][j].getType() != -1)
						{
							Layer2[i][j].TShow( (j - bgFrame)*86, i * 30);
							
						}
					}
				}
				////CharFrame = std::max(0, CharFrame);
				CharFrame++;
				CharFrame %= 8;
				Button[back_].TShow(20, 570);

				//show character
				Char->PutOnGround(Layer2, M_W_2, bgFrame,86,30);
				Char->TShow(-1, -1, &Clip[CharFrame]);

				//show gate
				if (Char->getState())
				{
					bgGate++;
					bgGate = bgGate % 42;
					std::string s = "image/water1/water900";
					std::string num = std::to_string(bgGate);
					while (num.size() != 2)num = "0" + num;
					s += num;
					s += ".png";
					Gate->loadFromFile(s);
					Gate->TShow(Char->getX() - 28, Char->getY() - 5);
					SDL_Delay(10);
				}

				//show heart and power
				for (int i = 0; i < Char->totalHeart(); ++i)
				{
					Heart.TShow(10 + i * 36, 10);
				}
				for (int i = 0; i < cur_power; ++i)
				{
					if (i < Char->totalPower())
					{
						if (i == 0)
							Pow[1][0].TShow(10 + i * 9, 40);
						else if (i < Char->totalPower() - 1)
							Pow[1][1].TShow(10 + i * 9, 40);
						else
							Pow[1][2].TShow(10 + i * 9, 40);
					}
					else
					{
						if (i == Char->totalPower() - 1)
							Pow[0][2].TShow(10 + i * 9, 40);
						else
							Pow[0][2].TShow(10 + i * 9, 40);
					}
				}
			
			}

			SDL_Delay(100);


		}
		if (bg_ == GAME_OVER)
		{
			Button[quit_].TShow(1200, 570);
			Button[back_].TShow(20, 570);
		}
		SDL_RenderPresent(Renderer);
		//Button[].TShow(200, 420);




	}
}



void Game::close()
{

	//Destroy window	
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	Renderer = NULL;
	Char = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
