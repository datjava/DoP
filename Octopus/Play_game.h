#include "Header.h"
#include "Tile.h"
#include "Button.h"
#include "generate_map.h"	
#include "Text.h"
#include "Character.h"
class Game
{
public:
	Game();
	~Game();
	bool init();
	bool MediaLoad();
	bool isRunning() { return !quit; }
	void CreateMap(const std::string& Path, MyTexture** Layer, int MAP_H, int MAP_W, char map_);
	void handleInput();
	void close();
	
private:
	SDL_Event e;
	SDL_Window* window ;
	SDL_Renderer* Renderer ;
	MyButton Button[TOTAL_BUTTONS];
	MyTexture BackgroundTexture[TOTAL_SCREEN_];
	MyCharacter* Char;
	SDL_Rect Clip[8],Clip_[4][8];
	MyTexture Heart, Pow[2][4];
	MyText Text ;
	int bg_ = MENU, alp = 255, dis = 1, dis_l = 2, cur_point = 0;
	int map = 1;
	int cur_power = 16;
	int bgFrame = 0;
	int bgGate = 0;
	int* arr;
	char MapType = '1';
	bool quit = false;
	MyTexture** Layer1 ;
	MyTexture** Layer2 ;
	MyTexture* Gate ;
};