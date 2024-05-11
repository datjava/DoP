#include "Character.h"
//MyCharacter
MyCharacter::MyCharacter(int x, int y)
{
	Texture = NULL;
	pos_x = x;
	pos_y = y;
	Width = 0;
	Height = 0;
	type = 0;
}
MyCharacter::~MyCharacter()
{
	free();
}
int MyCharacter::Check(MyTexture** layer)
{
	int j = (pos_x ) / 16 ;
	int i = (pos_y ) / 16 + 1;
	//std::cout << i << ' ' << j << '\n' << layer[i][j].getType()<<'\n';
	if (layer[i][j].getType() == -1)
	{

		return 1;
	}
	return 0;
}
void MyCharacter::Update(MyTexture** layer,double x,double y)
{
	//std::cout << a[bgFrame] << '\n';
	pos_x += x;
	pos_y += y;
	if (Check(layer) == 0)
	{
		pos_x -= x;
		pos_y -= y;
	}
}