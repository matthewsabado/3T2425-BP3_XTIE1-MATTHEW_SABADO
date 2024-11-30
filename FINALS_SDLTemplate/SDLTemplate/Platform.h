#pragma once
#include "GameObject.h"
#include "draw.h"
#include "common.h"

class Platform : public GameObject
{
public:
	void start();
	void update();
	void draw();

	//getters

	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();

	void spawn(int posX, int posY);

private:
	int x;
	int y;
	int height;
	int width;
	int speed;

	SDL_Texture* texture;

};

