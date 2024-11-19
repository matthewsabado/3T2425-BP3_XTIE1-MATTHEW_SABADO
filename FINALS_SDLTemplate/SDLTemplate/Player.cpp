#include "Player.h"

void Player::start()
{   
	x = SCREEN_WIDTH / 2 - 24;
	y = 750;
	texture = loadTexture("gfx/player.png");
	speed = 7;
	maximumJumpHeight = y - jumpPower;
	characterVelocity = 0;
	jumpTimer = 100;
	isGrounded = false;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Player::update()
{	
	if (y <= maximumJumpHeight)
	{
		isGrounded = false;
	}

	if (isGrounded == false)
	{
		characterVelocity += gravity / 2;
		y += characterVelocity;
	}

	if (app.keyboard[SDL_SCANCODE_LEFT])
	{
		x -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_RIGHT])
	{
		x += speed;
	}

	if (app.keyboard[SDL_SCANCODE_SPACE] && isGrounded)
	{
		y -= jumpPower;
		
	}


	if (!app.keyboard[SDL_SCANCODE_SPACE])
	{
		isGrounded = false;
	}

	if (y > 903)
	{
		isGrounded = true;
		characterVelocity = 0;
		y = 903;
	}
}

void Player::draw()
{
	blit(texture, x, y);
}
