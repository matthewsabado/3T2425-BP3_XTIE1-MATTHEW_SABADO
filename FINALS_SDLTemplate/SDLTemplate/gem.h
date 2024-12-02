#pragma once
#include "GameObject.h"
#include "draw.h"
#include "SoundManager.h"

class gem : public GameObject
{
public:

	void start();
	void update();
	void draw();

	int getPositionX();
	int getPositionY();
	int getHeight();
	int getWidth();

	void spawnGem(int posX, int posY);
	void setPosition(int posX, int posY);

private:
	int x;
	int y;
	int width;
	int height;

	int directionY;
	int directionChangeTime;
	int currentDirectionChangeTime;
	int speed;

	SDL_Texture* texture;

};

