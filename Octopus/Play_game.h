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
	std::vector<std::pair<MyButton,MyText>*> Button;
	std::vector<MyTexture*> Skill;
	std::vector<MyCharacter*> Monster;
	MyTexture BackgroundTexture[TOTAL_SCREEN_];
	MyCharacter* Char;
	SDL_Rect Clip[8],Clip_[4];
	MyTexture Heart, Pow[2][4];
	int bg_ = MENU, alp = 255, dis = 1, dis_l = 2, cur_point = 0;
	int map = 1;
	int cur_power = 16;
	int curBg = 0;
	int totalSkill = 12;
	int attackFrame = 0;
	int totalMonster = 18;
	int monsterFrame = 0;
	std::vector<SDL_Point> arr;
	char MapType = '1';
	bool quit = false;
	bool attack = false;
	MyTexture* Layer1 ;
	MyTexture** Layer2 ;
};