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
const int TILE_LY2 = 32;
const int M_W_1 = 20;
const int M_H_1 = 11;
const int M_W_2 = 180;
const int M_H_2 = 18;
const int WalkLeft = -5;
const int WalkRight = 5;
const int WalkRight1 = 86 * 2;
const int WalkUp = -120;
const int WalkDown = 6;
const int Char_WIDTH = 60;
const int Char_HEIGHT = 64;
static int RowNum = 0;

enum Screen_
{
	MENU,
	MAIN,
	SETTING_CHAR,
	SETTING_MAP,
	GAME_OVER,
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
	void TShow(int x = -1, int y = -1, SDL_Rect* clip = NULL);

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
	int pos_x;
	int pos_y;
	int Width;
	int Height;
	int type;
	

};
class MyText : public MyTexture
{
public:
	MyText(int x = 0, int y = 0);
	~MyText();
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
private:


};
//static SDL_Event e;
//static SDL_Window* window = NULL;
//static SDL_Renderer* Renderer = NULL;
static TTF_Font* gFont = NULL;
static void CreateMap(const std::string &Path, MyTexture **Layer, int MAP_H, int MAP_W, char _map);
#endif