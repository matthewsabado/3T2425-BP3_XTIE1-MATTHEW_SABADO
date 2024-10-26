#pragma once
#include "GameObject.h"
#include "SoundManager.h"

class PowerUp : public GameObject
{
public:
	void start();
	void update();
	void draw();
	void setPosition(int x, int y);

	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();

	int getPowerID();
	int powerID;
	

private:

	int x;
	int y;
	int width;
	int height;
	int directionX;
	int directionY;
	int speed;
	int directionChangeTime;
	int currentDirectionChangeTime;
	
	

	SDL_Texture* texture;
	Mix_Chunk* sound;

};

