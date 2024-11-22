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

	//movement variables
	const float jumpPower = 11.3f;
	int maximumJumpHeight;
	int jumpTracker;
	const float gravity = 3.8f;
	int characterVelocity;
	int speed;
	int isGrounded;
	int jumpTimer;

	//dash
	bool isDashCooldown;
	bool isDashPressed;
	bool isDashing;
	int dashSpeed;
	int dashDuration;
	int dashCooldown;

	SDL_Texture* texture;
};

