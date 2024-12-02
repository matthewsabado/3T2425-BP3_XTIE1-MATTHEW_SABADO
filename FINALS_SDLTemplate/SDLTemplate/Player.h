#pragma once
#include "GameObject.h"
#include "draw.h"
#include "common.h"
#include "SoundManager.h"

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

	void revive();
	void die();

	bool getDashCooldown();

private:
	int x;
	int y;
	int width;
	int height;
	bool isAlive;
	bool isDashSFX;

	//movement variables
	const float jumpPower = 20.3f;
	int maximumJumpHeight;
	int jumpTracker;
	const float gravity = 3.8f;
	int velocity;
	int maxVelocity;
	int speed;
	int isGrounded;
	int dashCooldown;
	bool hasJumped;

	//dash
	bool isDashCooldown;
	bool isDashPressed;
	bool isDashing;
	int dashSpeed;
	int dashDuration;


	Mix_Chunk* jumpSFX;
	Mix_Chunk* dash;
	SDL_Texture* texture;
};

