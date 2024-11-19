#pragma once
#include "GameObject.h"
#include "draw.h"
#include "common.h"
class Player : public GameObject
{
public:
	void start();
	void update();
	void draw();
private:
	int x;
	int y;
	int width;
	int height;
	const float jumpPower = 10.3f;
	int maximumJumpHeight;
	int jumpTracker;
	const float gravity = 5.8f;
	int characterVelocity;
	int speed;
	int isGrounded;
	int jumpTimer;

	SDL_Texture* texture;
};

