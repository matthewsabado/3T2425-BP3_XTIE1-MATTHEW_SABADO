#include "Player.h"

void Player::start()
{   
	x = SCREEN_WIDTH / 2 - 24;
	y = 750;
	texture = loadTexture("gfx/player.png");
	speed = 10;
	maximumJumpHeight = y - jumpPower;
	characterVelocity = 0;

	dashDuration = 0;
	dashCooldown = 100;
	dashSpeed = 24;
	isGrounded = false;
	isDashing = false;
	isDashPressed = false;
	isDashCooldown = false;

	isAlive = true;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Player::update()
{
	applyGravity();

	if (!isAlive) return;

	if (app.keyboard[SDL_SCANCODE_UP] && app.keyboard[SDL_SCANCODE_X] && !isDashPressed && isDashCooldown == false)
	{
		isDashCooldown = true;
		isDashing = true;
		dashDuration = 4;
		isDashPressed = true;
	}

	if (app.keyboard[SDL_SCANCODE_DOWN] && app.keyboard[SDL_SCANCODE_X] && !isDashPressed && isDashCooldown == false)
	{
		isDashCooldown = true;
		isDashing = true;
		dashDuration = 7;
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

	if (app.keyboard[SDL_SCANCODE_C])
	{
		jump();

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



	if (dashDuration == 0)
	{
		isDashing = false;
		isDashPressed = true;

	}

	if (!app.keyboard[SDL_SCANCODE_X])
	{
		isDashPressed = false;
	}



	//dash cooldown
	if (isDashCooldown)
	{
		dashCooldown--;
		if (dashCooldown <= 0)
		{
			isDashCooldown = false;
			dashCooldown = 100;
		}
	}

	//floor
	if (y > 703)
	{
		isGrounded = true;
		characterVelocity = 0;
		y = 703;
	}

	else
	{
		isGrounded = false;
	}

	//teleport to other side

	if (x + width < 0)
	{
		x = SCREEN_WIDTH;
	}

	else if (x > SCREEN_WIDTH)
	{
		x = -width;
	}
}

void Player::draw()
{
	blit(texture, x, y);
}

int Player::getPositionX()
{
	return this->x;
}

int Player::getPositionY()
{
	return this->y;
}

int Player::getWidth()
{
	return this->width;
}

int Player::getHeight()
{
	return this->height;
}

int Player::getVelocity()
{
	return this -> characterVelocity;
}

bool Player::getIsGrounded()
{
	return isGrounded;
}

bool Player::getIsAlive()
{
	return isAlive;
}

void Player::setPositionX(int posX)
{
	x = posX;
}

void Player::setPositionY(int posY)
{
	y = posY;

}

void Player::setVelocity(int newVel)
{
	characterVelocity = newVel;
}

void Player::setIsGrounded(bool grounded)
{
	isGrounded = grounded;
}

void Player::applyGravity()
{
	if (!isGrounded && !isDashing)
	{
		characterVelocity += gravity / 2;
	}

	y += characterVelocity;
}

void Player::jump()
{
	if (isGrounded && isDashing == false)
	{
		characterVelocity = -jumpPower;
		isGrounded = false;

	}
}

