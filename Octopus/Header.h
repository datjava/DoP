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
#include <vector>
#include<cmath>
#include<algorithm>
#include <cstring>
#include<random>
#include<set>
#include<queue>
//Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 675;
//Key press surfaces constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
//Tile dimension contants
const int TILE_LY1 = 64;
const int TILE_LY2 = 32;
const int M_W_1 = 20;
const int M_H_1 = 11;
const int M_W_2 = 70;
const int M_H_2 = 40;
const int WalkLeft = -5;
const int WalkRight = 5;
const int WalkUp = -5;
const int WalkDown = 5;
const int monster_move = 6;
const int Char_WIDTH = 60;
const int Char_HEIGHT = 64;
static int RowNum = 0;
enum Screen_
{
	MENU,
	MAIN,
	CHAR,
	SKILL,
	GAME_OVER,
	TOTAL_SCREEN_
};
enum Buttons
{
	play_,
	quit_,
	char_,
	skill_1,
	skill_2,
	skill_,
	back_,
	confirm_,
	char_1,
	char_2,
	char_3,
	TOTAL_BUTTONS

};
class MyTexture
{
public:
	//Initializes variables
	MyTexture( int x = 0, int y = 0);

	//Deallocates memory
	~MyTexture();

	//Deallocates texture
	void free();

	//set renderer
	void setRenderer(SDL_Renderer* _renderer);
	//Loads image at specified path
	bool loadFromFile(std::string path = "", int value = 0);

	//Renders texture at given point
	void TShow(double x = -1, double y = -1, SDL_Rect* clip = NULL);

	//Gets image dimensions
	int getWidth();
	int getHeight();
	void setAlpha(Uint8 alpha);
	//Get type of texture
	int getType() { return type; }
	//return texture
	SDL_Texture* getTexture() { return Texture; }
protected:
	//The actual hardware texture
	SDL_Texture* Texture;
	SDL_Renderer* renderer;
	//Image dimensions
	double pos_x;
	double pos_y;
	int Width;
	int Height;
	int type;
	

};

static void CreateMap(const std::string &Path, MyTexture **Layer, int MAP_H, int MAP_W, char _map);
#endif