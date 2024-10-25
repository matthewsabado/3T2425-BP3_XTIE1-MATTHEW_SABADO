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

	int powerId;

	SDL_Texture* triShotTexture;
	SDL_Texture* rapidShotTexture;
	Mix_Chunk* sound;

};

