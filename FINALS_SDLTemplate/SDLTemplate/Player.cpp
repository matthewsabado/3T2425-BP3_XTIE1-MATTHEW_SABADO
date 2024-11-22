#include "Player.h"

void Player::start()
{   
	x = SCREEN_WIDTH / 2 - 24;
	y = 750;
	texture = loadTexture("gfx/player.png");
	speed = 10;
	maximumJumpHeight = y - jumpPower;
	characterVelocity = 0;
	jumpTimer = 100;

	dashDuration = 0;
	dashCooldown = 100;
	dashSpeed = 24;
	isGrounded = false;
	isDashing = false;
	isDashPressed = false;
	isDashCooldown = false;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Player::update()
{	
	std::cout << isDashCooldown;

	if (y <= maximumJumpHeight)
	{
		isGrounded = false;
	}

	//gravity
	if (isGrounded == false && isDashing == false)
	{
		characterVelocity += gravity / 2;
		y += characterVelocity;
	}

	if (app.keyboard[SDL_SCANCODE_UP] && app.keyboard[SDL_SCANCODE_X] && !isDashPressed && isDashCooldown == false)
	{
		isDashCooldown = true;
		isDashing = true;
		dashDuration = 8;
		isDashPressed = true;
	}

	if (app.keyboard[SDL_SCANCODE_DOWN] && app.keyboard[SDL_SCANCODE_X] && !isDashPressed && isDashCooldown == false)
	{
		isDashCooldown = true;
		isDashing = true;
		dashDuration = 5;
		isDashPressed = true;
	}

	if (app.keyboard[SDL_SCANCODE_LEFT])
	{
		x -= speed;

		if (app.keyboard[SDL_SCANCODE_X] && !isDashPressed && isDashCooldown == false)
		{
			isDashCooldown = true;
			isDashing = true;
			dashDuration = 5;
			isDashPressed = true;
		}
	}

	if (app.keyboard[SDL_SCANCODE_RIGHT])
	{
		x += speed;

		if (app.keyboard[SDL_SCANCODE_X] && !isDashPressed && isDashCooldown == false)
		{
			isDashCooldown = true;
			isDashing = true;
			dashDuration = 5;
			isDashPressed = true;
			
		}
	}

	if (isDashing)
	{
		if (app.keyboard[SDL_SCANCODE_RIGHT])
		{
			x += dashSpeed;
		}

		if (app.keyboard[SDL_SCANCODE_LEFT])
		{
			x -= dashSpeed;
		}

		if (app.keyboard[SDL_SCANCODE_UP])
		{
			y -= dashSpeed;
		}

		if (app.keyboard[SDL_SCANCODE_DOWN])
		{
			y += dashSpeed;
		}

		dashDuration--;

	}

	if (isDashCooldown == true)
	{
		dashCooldown--;

	}

	if (dashCooldown == 0)
	{
		isDashCooldown = false;
	}


	if (dashDuration == 0)
	{
		isDashing = false;
		isDashPressed = true;

	}

	if (!app.keyboard[SDL_SCANCODE_X])
	{
		isDashPressed = false;
	}

	if (app.keyboard[SDL_SCANCODE_C] && isGrounded)
	{
		y -= jumpPower;
		
	}


	if (!app.keyboard[SDL_SCANCODE_C])
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

