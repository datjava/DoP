#include "Play_game.h"
Game::Game()
{

	window = NULL;
	Renderer = NULL;
	Char = NULL;
	bg_ = MENU, alp = 255, dis = 1, dis_l = 1, cur_point = 0;
	cur_power = 16;
	MapType = '1';
	Layer1 = NULL;
	Layer2 = NULL;
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
		generate_layer3(n, m);

	}
	//load background texture
	for (int i = 0; i < TOTAL_SCREEN_; ++i)
		BackgroundTexture[i].setRenderer(Renderer);
	if (BackgroundTexture[MENU].loadFromFile("image/MENU.png") == 0)
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}
	if (BackgroundTexture[GAME_OVER].loadFromFile("image/GAMEOVER.png") == 0)
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}
	if (BackgroundTexture[MAIN].loadFromFile("image/th.jpg") == 0)
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}
	//load character texture
	Char = new std::pair<MyCharacter, MyText>;
	Char->first = MyCharacter(500, 120);
	Char->first.setRenderer(Renderer);
	Char->second.setRenderer(Renderer);
	Char->second.setFont(10, "font/lazy.ttf");
	Char->second.loadFromRenderedText(std::to_string(Char->first.getPower()), { 255,255,255 });
	if (Char->first.loadFromFile("image/ch0.png") == 0)
	{
		printf("Failed to load character texture image!\n");
		success = false;
	}
	//load monster
	for (int i = 0; i < 10; i++)
	{
		std::pair<MyCharacter, MyText>* temp = new std::pair<MyCharacter, MyText>;
		temp->first = MyCharacter(70 + rand() % 32, 40 + i * 64);
		temp->first.setRenderer(Renderer);
		temp->first.changePower(rand() % 10 + 1);
		temp->second.setRenderer(Renderer);
		temp->second.setFont(8, "font/lazy.ttf");
		temp->second.loadFromRenderedText(std::to_string(temp->first.getPower()), { 255,255,255 });
		std::string s = "image/ch";
		std::string num = std::to_string(i % 4 + 1);
		//while (num.size() != 2)num = "0" + num;
		s += num;
		s += ".png";
		if (temp->first.loadFromFile(s) == 0)
		{
			printf("Failed to load monster texture image!\n");
			success = false;
		}
		if (temp != NULL)
			Monster.push_back(temp);
		else
		{
			printf("Failed to load monster texture image!\n");
		}
	}
	//load button texture
	for (int i = 0; i < TOTAL_BUTTONS; ++i)
	{
		std::pair<MyButton, MyText>* temp = new std::pair<MyButton, MyText>;
		temp->first.setRenderer(Renderer);
		temp->second.setRenderer(Renderer);
		temp->second.setFont(25, "font/lazy.ttf");
		switch (i)
		{
		case play_:
			if (temp->second.loadFromRenderedText("Play", { 255,255,255 }) == 0)
			{
				printf("Failed to load text texture image!\n");
				success = false;
			}
			if (temp->first.loadFromFile("image/green_button00.png") == 0)
			{
				printf("1Failed to load button texture image!\n");
				success = false;
			}
			break;
		case quit_:
			if (temp->second.loadFromRenderedText("Quit", { 255,255,255 }) == 0)
			{


				//"D:\lib\DoP\Octopus\image/green_button00.png"
				printf("Failed to load text texture image!\n");
				success = false;
			}
			if (temp->first.loadFromFile("image/green_button00.png") == 0)
			{
				printf("2Failed to load button texture image!\n");
				success = false;
			}
			break;
		case back_:
			if (temp->first.loadFromFile("image/back1.png") == 0)
			{
				printf("5Failed to load button texture image!\n");
				success = false;
			}
			break;
		case confirm_:
			if (temp->first.loadFromFile("image/confirm1.png") == 0)
			{
				printf("6Failed to load button texture image!\n");
				success = false;
			}
			break;
		default:
			break;
		}

		if (temp != NULL)Button.push_back(temp);
		else
		{
			printf("Failed to load button texture image!\n");
		}
	}
	//load clip
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Clip[i * 4 + j].x = j * 32;
			Clip[i * 4 + j].y = i * 32;
			Clip[i * 4 + j].w = 32;
			Clip[i * 4 + j].h = 32;
		}
	}
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			Clip_[i * 8 + j].x = j * 32;
			Clip_[i * 8 + j].y = i * 25;
			Clip_[i * 8 + j].w = 32;
			Clip_[i * 8 + j].h = 25;
		}
	}
	//Load tile texture
	Layer2 = new MyTexture * [n];
	for (int i = 0; i < n; ++i)
	{
		Layer2[i] = new MyTexture[m];
	}
	//CreateMap("image/map.txt", Layer1, M_H_1, M_W_1, MapType);
	CreateMap("image/map.txt", Layer2, n, m, MapType);
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
				std::string s = "image/tile_bg/map/tile_00";
				//s += map_;
				//std::cout << s << '\n';
				while (value.size() != 2)value = "0" + value;
				s += value;
				s += ".png";

				if (v != 0 && v != -1)
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
	int CharFrame = 5;
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
				for (int i = 0; i < Button.size(); ++i)
				{
					if (Button[i]->first.handleEvent(e) == true)
					{
						if (bg_ == MENU)
						{
							switch (i)
							{
							case play_:
								if (Char == NULL)
								{
									/*Char->first = MyCharacter(70,120);
									Char->first.setRenderer(Renderer);*/
									MediaLoad();
								}
								bg_ = MAIN;
								break;
							case quit_:
								quit = true;
								break;
							case skill_:
								bg_ = SKILL;
								break;
							case char_:
								bg_ = CHAR;
								break;
							}
						}
						switch (i)
						{
						case confirm_:
							switch (bg_)
							{
							case CHAR:
								bg_ = MENU;
								break;
							}
							break;
						case back_:
							switch (bg_)
							{
							case CHAR:
								bg_ = MENU;
								break;
							case MAIN:
								bg_ = MENU;
								break;
							case GAME_OVER:
								bg_ = MENU;
								break;
							}
							break;
						default:
							break;
						}
					}
				}
			}
			else if (e.type == SDL_KEYDOWN)
			{
				/*if (Char != NULL)
				{
					Char->first.Update(Layer2, e, arr, curBg);
					if (e.key.keysym.sym == SDLK_SPACE)
					{
						attack = true;
					}
					CharFrame++;
				}*/
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
			//std::cout << Button.size() << '\n';
			Button[play_]->first.TShow(200, 350);
			/*Button[skill_]->first.TShow(200, 420);
			Button[char_]->first.TShow(200, 490);*/
			Button[quit_]->first.TShow(200, 560);
			Button[play_]->second.TShow(250, 360);
			/*Button[skill_]->second.TShow(250, 430);
			Button[char_]->second.TShow(250, 500);*/
			Button[quit_]->second.TShow(250, 570);
		}
		if (Char != NULL && bg_ == MAIN)
		{
			if (Char != NULL)
			{
				//show map
				for (int i = 0; i < M_H_2; ++i)
				{
					for (int j = 0; j < M_W_2; ++j)
					{
						Layer2[i][j].TShow(j * 16 + 30, i * 16 + 30);
					}
				}
				CharFrame++;
				CharFrame %= 21;
				monsterFrame++;
				monsterFrame %= 16;
				Button[back_]->first.TShow(20, 570);
				int x = 0, y = 0;
				int mx;
				int my;
				SDL_GetMouseState(&mx, &my);
				x = mx - Char->first.getX();
				y = my - Char->first.getY();
				x /= 29;
				y /= 29;
				//show other
				srand(time(NULL));
				for (int i = 0; i < Monster.size(); i++)
				{
					int x_m = Monster[i]->first.getX();
					int y_m = Monster[i]->first.getY();
					int x_c = Char->first.getX() + x;
					int y_c = Char->first.getY() + y;
					//check xm ym
					//std::cout << Monster[i]->first.getPower() << '\n';
					if(x_c <= x_m && x_m <= x_c + 32 && y_c <= y_m && y_m <= y_c + 25)
					{
						
						Char->first.changePower(Monster[i]->first.getPower());Monster.erase(Monster.begin() + i);
					}
					//check xm +32 ym
					else if (x_c <= x_m + 32 && x_m + 32 <= x_c + 32 && y_c <= y_m && y_m <= y_c + 25)
					{
						
						Char->first.changePower(Monster[i]->first.getPower());Monster.erase(Monster.begin() + i);
					}
					//check xm ym + 32
					else if(x_c <= x_m && x_m <= x_c + 32 && y_c <= y_m + 25 && y_m + 25 <= y_c + 25)
					{
						
						Char->first.changePower(Monster[i]->first.getPower());Monster.erase(Monster.begin() + i);
					}
					//check xm + 32 ym + 32
					else if (x_c <= x_m + 32 && x_m + 32 <= x_c + 32 && y_c <= y_m + 25 && y_m + 25 <= y_c + 25)
					{
						
						Char->first.changePower(Monster[i]->first.getPower());Monster.erase(Monster.begin() + i);
					}
				}
				for (int i = 0; i < Monster.size(); ++i)
				{
					int x_m = Monster[i]->first.getX();
					int y_m = Monster[i]->first.getY();
					if (x_m < 0 || x_m > SCREEN_WIDTH || y_m < 0 || y_m > SCREEN_HEIGHT)
					{
						Monster.erase(Monster.begin() + i);
					}
					else
					{
						x_m += rand() % 4;
						y_m += rand() % 2;
						Monster[i]->first.TShow(x_m, y_m, &Clip[monsterFrame]);
						Monster[i]->second.TShow(x_m, y_m);

					}
				}
				//render time
				SDL_GetTicks();
				if (Monster.size() <= 100 && SDL_GetTicks() % 100 == 0)
				{
					std::pair<MyCharacter, MyText>* temp = new std::pair<MyCharacter, MyText>;
					temp->first = MyCharacter(70 + rand() % 32, 40);
					temp->first.setRenderer(Renderer);
					temp->first.changePower(rand() % 10 + 1);
					temp->second.setRenderer(Renderer);
					temp->second.setFont(10, "font/lazy.ttf");
					temp->second.loadFromRenderedText(std::to_string(temp->first.getPower()), { 255,255,255 });
					std::string s = "image/ch";
					std::string num = std::to_string(rand() % 5 + 1);
					//while (num.size() != 2)num = "0" + num;
					s += num;
					s += ".png";
					if (temp->first.loadFromFile(s) == 0)
					{
						printf("Failed to load monster texture image!\n");

					}
					if (temp != NULL)
						Monster.push_back(temp);
					else
					{
						printf("Failed to load monster texture image!\n");
					}
				}
				//show character
				Char->first.Update(Layer2, x, y);
				Char->first.TShow(-1, -1, &Clip_[CharFrame]);
				Char->second.loadFromRenderedText(std::to_string(Char->first.getPower()), { 255,255,255 });
				Char->second.TShow(Char->first.getX(), Char->first.getY());
			}


			SDL_Delay(50);

		}
		if (bg_ == GAME_OVER)
		{
			Button[quit_]->first.TShow(1200, 570);
			Button[back_]->first.TShow(20, 570);
		}
		SDL_RenderPresent(Renderer);
	}

	//Button[].TShow(200, 420);




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
