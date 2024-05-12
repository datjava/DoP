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
	std::vector<std::pair<MyCharacter,MyText>*> Monster;
	MyTexture BackgroundTexture[TOTAL_SCREEN_];
	std::pair<MyCharacter,MyText>* Char;
	MyText* time = NULL,*Num = NULL,*curState = NULL;
	SDL_Rect Clip[16],Clip_[21];
	int bg_ = MENU, alp = 255, dis = 1, dis_l = 2, cur_point = 0;
	int map = 1;
	int cur_power = 16;
	int curBg = 0;
	int totalSkill = 12;
	int attackFrame = 0;
	int monsterFrame = 0;
	int curTime = 0, passTime = 0, gapTime = 60,cnt = 0,curNum = -1,magicNum = 200,timeLimit = 300;
	std::vector<SDL_Point> arr;
	char MapType = '1';
	bool quit = false;
	bool attack = false;
	MyTexture* Layer1 ;
	MyTexture** Layer2 ;
};