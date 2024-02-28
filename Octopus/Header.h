#ifndef HEADER_H_
#define HEADER_H_
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <fstream>	
#include <map>
#include <map>
#include <utility>
//Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 675;
//Key press surfaces constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
//Tile dimension contants
const int TILE_LY1 = 64;
const int TILE_LY2 = 18;
const int M_W_1 = 20;
const int M_H_1 = 11;
const int M_W_2 = 70;
const int M_H_2 = 38;
const int WalkLeft = -20;
const int WalkRight = 18;
const int WalkRight1 = 18 + 18 * 3;
const int WalkUp = -60;
const int WalkDown = 6;
const int Char_WIDTH = 60;
const int Char_HEIGHT = 64;
int RowNum = 0;
int bgFrame = 0;
enum Screen_
{
	MENU,
	MAIN,
	SETTING_CHAR,
	SETTING_MAP,
	//GAME_OVER,
	TOTAL_SCREEN_
};
enum Buttons
{
	play_,
	quit_,
	settings_,
	back_,
	map_1,
	map_2,
	confirm_,
	char_1,
	char_2,
	char_3,
	TOTAL_BUTTONS

};
static SDL_Window* window = NULL;
static SDL_Renderer* Renderer = NULL;
class MyTexture
{
public:
	//Initializes variables
	MyTexture(int x = 0, int y = 0);

	//Deallocates memory
	~MyTexture();

	//Deallocates texture
	void free();

	//Loads image at specified path
	bool loadFromFile(std::string path = "", int value = 0);

	//Renders texture at given point
	void TShow(int x = -1, int y = -1, SDL_Rect* clip = NULL);

	//Gets image dimensions
	int getWidth();
	int getHeight();
	void setAlpha(Uint8 alpha);
	//Get type of texture
	int getType() { return type; }

protected:
	//The actual hardware texture
	SDL_Texture* Texture;
	//Image dimensions
	int pos_x;
	int pos_y;
	int Width;
	int Height;
	int type;
	std::string Path[2];
};
class MyTile : public MyTexture
{
public:
	MyTile(int x = 0, int y = 0);
	~MyTile();
	int getType() { return type; }
};
class MyCharacter : public MyTexture
{
public:
	MyCharacter(int x = 0, int y = 0);
	~MyCharacter();
	bool Update(SDL_Event& e);
	void Check();
	void PutOnGround();
	int getY() { return pos_y; }
	int totalHeart() { return heart; }
	int totalPower() { return power; }
private:
	bool isOnGround = 0;
	int heart = 3;
	int power = 16;
};
class MyButton : public MyTexture
{
public:
	MyButton(int x = 0, int y = 0);
	~MyButton();
	bool handleEvent(const SDL_Event& e);
	bool IsInside(int m_x, int m_y);
	void givePath(std::string path1, std::string path2);
	int getCnt() { return cnt; }
private:
	int cnt = 0;
};
class MyText : public MyTexture
{
public:
	MyText(int x = 0, int y = 0);
	~MyText();
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
private:


};
TTF_Font* gFont = NULL;
MyTexture BackgroundTexture[TOTAL_SCREEN_];
MyButton Button[TOTAL_BUTTONS];
MyCharacter Char;
SDL_Rect Clip[8];
MyTexture **Layer1 = NULL, **Layer2 = NULL, **Layer3 = NULL;
MyTexture Heart,Pow[2][4];
MyText Text = NULL;
int bg_ = MENU,alp = 255,dis = 1,dis_l = 1,cur_point = 0;
int cur_power = 16;
char MapType = '1';
void CreateMap(const std::string &Path, MyTexture **Layer, int MAP_H, int MAP_W, char _map);
#endif