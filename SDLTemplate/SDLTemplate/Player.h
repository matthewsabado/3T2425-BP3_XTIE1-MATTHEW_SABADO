#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>

using namespace std;

class Player : public GameObject
{
public:
	~Player();
	void start();
	void update();
	void draw();
	
	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight(); 

	bool getIsAlive();
	void die();

private:
	float x;
	float y;
	float velocityX;
	float velocityY;
	int width;
	int height;
	int speed;
	const int baseSpeed = 3;

	float mainReloadTime;
	float currentMainReloadTime;
	float sideReloadTime;
	float currentSideReloadTime;

	SDL_Texture* texture;
	Mix_Chunk* sound;

	vector<Bullet*> bullets;

	bool isAlive;
};

