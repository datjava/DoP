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
	if (BackgroundTexture[CHAR].loadFromFile("image/Char.png") == 0)
	{
		printf("Failed to load background texture image!\n");
		success = false;

	}
	if (BackgroundTexture[SKILL].loadFromFile("image/skill.png") == 0)
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
	Char = new MyCharacter(70, 120);
	Char->setRenderer(Renderer);
	if (Char->loadFromFile("image/Pink_Monster_Run_6.png") == 0)
	{
		printf("Failed to load character texture image!\n");
		success = false;
	}
	//load monster
	for (int i = 0; i < totalMonster; i++)
	{
		MyCharacter* temp = new MyCharacter;
		temp->setRenderer(Renderer);
		std::string s = "image/monster/";
		std::string num = std::to_string(i);
		//while (num.size() != 2)num = "0" + num;
		s += num;
		s += ".png";
		if (temp->loadFromFile(s) == 0)
		{
			printf("Failed to load monster texture image!\n");
			success = false;
		}
		Monster.push_back(temp);
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
		case char_:
			if (temp->second.loadFromRenderedText("Char", { 255,255,255 }) == 0)
			{
				printf("Failed to load text texture image!\n");
				success = false;
			}

			if (temp->first.loadFromFile("image/green_button00.png") == 0)
			{
				printf("3Failed to load button texture image!\n");
				success = false;
			}
			break;
		case skill_:
			if (temp->first.loadFromFile("image/green_button00.png") == 0)
			{
				printf("4Failed to load button texture image!\n");
				success = false;
			}
			if (temp->second.loadFromRenderedText("Skill", { 255,255,255 }) == 0)
			{
				printf("Failed to load text texture image!\n");
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
		case char_1:
			if (temp->first.loadFromFile("image/char1.png") == 0)
			{
				printf("Failed to load button texture image!\n");
				success = false;
			}
			break;
		case char_2:
			if (temp->first.loadFromFile("image/char2.png") == 0)
			{
				printf("Failed to load button texture image!\n");
				success = false;
			}
			break;
		case char_3:
			if (temp->first.loadFromFile("image/char3.png") == 0)
			{
				printf("Failed to load button texture image!\n");
				success = false;
			}
			break;
		case skill_1:
			if (temp->first.loadFromFile("image/water.png") == 0)
			{
				printf("Failed to load button texture image!\n");
				success = false;
			}
			break;
		case skill_2:
			if (temp->first.loadFromFile("image/fire.png") == 0)
			{
				printf("Failed to load button texture image!\n");
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
	for (int i = 0; i < 4; ++i)
	{
		Clip_[i].x = i * 16;
		Clip_[i].y = 0;
		Clip_[i].w = 16;
		Clip_[i].h = 16;
	}
	//Load tile texture
	Layer2 = new MyTexture * [M_H_2];
	for (int i = 0; i < n; ++i)
	{
		Layer2[i] = new MyTexture[m];
	}
	//CreateMap("image/map.txt", Layer1, M_H_1, M_W_1, MapType);
	CreateMap("image/map.txt", Layer2, n, m, MapType);
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
	//load skill
	for (int i = 0; i < totalSkill; ++i)
	{
		MyTexture* temp = new MyTexture;
		temp->setRenderer(Renderer);
		std::string s = "image/water1/skill1/";
		std::string num = std::to_string(i);
		while (num.size() != 2)num = "0" + num;
		s += num;
		s += ".png";
		if (temp->loadFromFile(s) == 0)
		{
			printf("Failed to load skill texture image!\n");
			success = false;
		}
		Skill.push_back(temp);
	}
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
									Char = new MyCharacter();
									Char->setRenderer(Renderer);
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
						if (bg_ == CHAR)
						{
							switch (i)
							{
							case char_1:
								//bg_ = 3;
								delete Char;
								Char = new MyCharacter(70, 120);
								Char->setRenderer(Renderer);
								if (Char->loadFromFile("image/Pink_Monster_Run_6.png") == 0)
								{
									printf("Failed to load character texture image!\n");
								}
								break;
							case char_3:
								//Char->loadFromFile("");
								delete Char;
								Char = new MyCharacter(70, 120);
								Char->setRenderer(Renderer);
								if (Char->loadFromFile("image/Dude_Monster_Run_6.png") == 0)
								{
									printf("Failed to load character texture image!\n");
								}
								break;
							case char_2:
								//Char->loadFromFile("");
								delete Char;
								Char = new MyCharacter(70, 120);
								Char->setRenderer(Renderer);
								if (Char->loadFromFile("image/Owlet_Monster_Run_6.png") == 0)
								{
									printf("Failed to load character texture image!\n");
								}
								//bg_ = 5;
								break;
							default:
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
							case SKILL:
								bg_ = MENU;
								break;
							}
							break;
						case back_:
							switch (bg_)
							{
							case SKILL:
								bg_ = MENU;
								break;
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
						if (bg_ == SKILL)
						{
							switch (i)
							{
							case skill_1:
								//bg_ = 3;
								totalSkill = 12;
								Skill.clear();
								for (int i = 0; i < totalSkill; ++i)
								{
									MyTexture* temp = new MyTexture;
									temp->setRenderer(Renderer);
									std::string s = "image/water1/skill1/";
									std::string num = std::to_string(i);
									while (num.size() != 2)num = "0" + num;
									s += num;
									s += ".png";
									if (temp->loadFromFile(s) == 0)
									{
										printf("Failed to load skill texture image!\n");
									}
									Skill.push_back(temp);
								}
								break;
							case skill_2:
								//Char->loadFromFile("");
								totalSkill = 39;
								Skill.clear();
								for (int i = 0; i < totalSkill; ++i)
								{
									MyTexture* temp = new MyTexture;
									temp->setRenderer(Renderer);
									std::string s = "image/fire1/skill1/";
									std::string num = std::to_string(i);
									while (num.size() != 2)num = "0" + num;
									s += num;
									s += ".png";
									if (temp->loadFromFile(s) == 0)
									{
										printf("Failed to load skill texture image!\n");
									}
									Skill.push_back(temp);
								}
								break;
							default:
								break;
							}
						}
					}
				}
			}
			else if (e.type == SDL_KEYDOWN)
			{
				if (Char != NULL)
				{
					Char->Update(Layer2, e, arr, curBg);
					if (e.key.keysym.sym == SDLK_SPACE)
					{
						attack = true;
					}
					CharFrame++;
				}
			}
			else if (e.type == SDL_KEYUP)
			{
				CharFrame = 5;
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
			Button[skill_]->first.TShow(200, 420);
			Button[char_]->first.TShow(200, 490);
			Button[quit_]->first.TShow(200, 560);
			Button[play_]->second.TShow(250, 360);
			Button[skill_]->second.TShow(250, 430);
			Button[char_]->second.TShow(250, 500);
			Button[quit_]->second.TShow(250, 570);
		}
		if (bg_ == CHAR)
		{
			Button[back_]->first.TShow(20, 570);
			Button[char_1]->first.TShow(330, 300);
			Button[char_2]->first.TShow(530, 300);
			Button[char_3]->first.TShow(730, 300);
			Button[confirm_]->first.TShow(1030, 570);
		}
		if (bg_ == SKILL)
		{
			Button[back_]->first.TShow(20, 570);
			Button[confirm_]->first.TShow(1030, 570);
			Button[skill_1]->first.TShow(330, 300);
			Button[skill_2]->first.TShow(530, 300);
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
				//show map
				for (int i = 0; i < M_H_2; ++i)
				{
					for (int j = 0; j < M_W_2; ++j)
					{
						Layer2[i][j].TShow(j * 16, i * 16);
					}
				}
				CharFrame %= 6;
				monsterFrame++;
				monsterFrame %= 4;
				Button[back_]->first.TShow(20, 570);

				//show character
				Char->TShow(-1, -1, &Clip[CharFrame]);
				//show monster
				for (int i = 0; i < totalMonster; ++i)
				{
					//calculate angle
					double angle = atan2(Char->getY() - Monster[i]->getY(), Char->getX() - Monster[i]->getX());
					double dx = cos(angle);
					double dy = sin(angle);
					std::cout << dx << ' ' << dy << '\n';
					Monster[i]->TShow(Monster[i]->getX() + dx,Monster[i]->getY() + dy, &Clip_[monsterFrame]);
				}
				//show skill
				if (attack == true)
				{
					if (attackFrame == totalSkill)attack = false;
					attackFrame %= totalSkill;
					Skill[attackFrame]->TShow(Char->getX() + 8, Char->getY() - 8);
					attackFrame++;
				}
				//show heart and power
				for (int i = 0; i < Char->totalHeart(); ++i)
				{
					Heart.TShow(10 + i * 36, 10);
				}
				for (int i = 0; i < cur_power; ++i)
				{
					if (i == 0)
					{
						Pow[0][0].TShow(10 + i * 18 + 9, 50);
					}
					else if (i == cur_power - 1)
					{
						Pow[0][2].TShow(10 + i * 18, 50);
					}
					else
					{
						Pow[0][1].TShow(10 + i * 18, 50);
					}
				}
				for (int i = 0; i < Char->totalPower(); ++i)
				{
					if (i == 0)
					{
						Pow[1][0].TShow(10 + i * 18 + 9, 50);
					}
					else if (i == Char->totalPower() - 1)
					{
						Pow[1][2].TShow(10 + i * 18, 50);
					}
					else
					{
						Pow[1][1].TShow(10 + i * 18, 50);
					}
				}

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
