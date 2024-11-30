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

	//getters
	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();
	int getVelocity();
	bool getIsGrounded();
	bool getIsAlive();

	void setPositionX(int posX);
	void setPositionY(int posY);
	void setVelocity(int newVel);
	void setIsGrounded(bool grounded);

	void applyGravity();
	void jump();

private:
	int x;
	int y;
	int width;
	int height;
	bool isAlive;

	//movement variables
	const float jumpPower = 24.3f;
	int maximumJumpHeight;
	int jumpTracker;
	const float gravity = 3.8f;
	int characterVelocity;
	int speed;
	int isGrounded;

	//dash
	bool isDashCooldown;
	bool isDashPressed;
	bool isDashing;
	int dashSpeed;
	int dashDuration;
	int dashCooldown;

	

	SDL_Texture* texture;
};

