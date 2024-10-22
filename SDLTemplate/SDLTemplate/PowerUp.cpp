#include "PowerUp.h"
#include "draw.h"

void PowerUp::start()
{
	texture = loadTexture("gfx/points.png");

	directionX = 1;
	directionY = 1;
	speed = 2;
	width = 0;
	height = 0;

	directionChangeTime = (rand() % 100) + 100; //Direction change every 3-8 seconds
	currentDirectionChangeTime = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

}

void PowerUp::update()
{
	x += directionX * speed;
	y += directionY * speed;

	//random movement here
	if (currentDirectionChangeTime > 0)
	{
		currentDirectionChangeTime--;
	}

	if (currentDirectionChangeTime == 0 || x < 0 || x > SCREEN_WIDTH)
	{
		directionX = -directionX;
		currentDirectionChangeTime = directionChangeTime;
	}

}

void PowerUp::draw()
{
	blit(texture, x, y);
}

void PowerUp::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;

}

int PowerUp::getPositionX()
{
	return this->x;
}

int PowerUp::getPositionY()
{
	return this->y;
}

int PowerUp::getWidth()
{
	return this->width;
}

int PowerUp::getHeight()
{
	return this->height;
}
