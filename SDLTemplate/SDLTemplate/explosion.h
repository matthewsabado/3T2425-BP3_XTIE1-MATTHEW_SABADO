#pragma once
#include "GameObject.h"
#include "draw.h"
#include "Scene.h"
#include "common.h"
#include "SoundManager.h"

class explosion : public GameObject
{
public:
	void start();
	void update();
	void draw();
	void setPosition(int x, int y);

private:
	int x;
	int y;
	int width;
	int height;
	int despawnTime;

	SDL_Texture* texture;
	Mix_Chunk* boom;
};

