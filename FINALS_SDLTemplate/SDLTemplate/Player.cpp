#include "Player.h"
using namespace std;

void Player::start()
{
	x = SCREEN_WIDTH / 2 - 24;
	y = 750;
	texture = loadTexture("gfx/player.png");
	speed = 10;
	maximumJumpHeight = y - jumpPower;
	velocity = 0;
	maxVelocity = 15;

	dashDuration = 0;
	dashCooldown = 100;
	dashSpeed = 24;

	isGrounded = false;
	isDashing = false;
	isDashPressed = false;
	isDashCooldown = false;
	isDashSFX = false;
	isAlive = true;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	jumpSFX = SoundManager::loadSound("sound/jump.mp3");
	dash = SoundManager::loadSound("sound/dash.wav");
}

void Player::update()
{

	/*cout << "Current X: " << x << endl;
	cout << "Current Y: " << y << endl;
	cout << "Current Velocity: " << velocity << endl;
	system("cls");*/

	applyGravity();

	if (!isAlive) return;

	if (isGrounded)
	{
		hasJumped = false;
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
		if (!isDashSFX)
		{
			SoundManager::playSound(dash);
			dash->volume = 10;
			isDashSFX = true;
		}
		
		if (app.keyboard[SDL_SCANCODE_RIGHT])
		{
			x += dashSpeed;
		}

		if (app.keyboard[SDL_SCANCODE_LEFT])
		{
			x -= dashSpeed;
		}

		dashDuration--;

	}

	else
	{
		isDashSFX = false;
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
		velocity = 0;
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
	if (!isAlive) return;
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
	return this->velocity;
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
	velocity = newVel;
}

void Player::setIsGrounded(bool grounded)
{
	if (grounded)
	{
		velocity = 0;
	}

	isGrounded = grounded;
}

void Player::applyGravity()
{
	if (!isGrounded && !isDashing)
	{
		velocity += gravity / 2;

		if (velocity > maxVelocity)
		{
			velocity = maxVelocity;
		}
	}

	y += velocity;
}

void Player::jump()
{
	
	if (isGrounded && isDashing == false && !hasJumped)
	{
		SoundManager::playSound(jumpSFX);
		jumpSFX->volume = 10;
		velocity = -jumpPower;
		isGrounded = false;

	}
}

void Player::revive()
{
	isAlive = true;
}

void Player::die()
{
	isAlive = false;
}

bool Player::getDashCooldown()
{
	return isDashCooldown;
}

