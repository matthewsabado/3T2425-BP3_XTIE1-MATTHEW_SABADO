#include "wormhole.h"

void wormhole::start()
{
	texture = loadTexture("gfx/gg.png");
	speed = 1;
	directionY = 1;
	directionChangeTime = 25;
	currentDirectionChangeTime = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void wormhole::update()
{
	y += directionY * speed;

	if (currentDirectionChangeTime > 0)
	{
		currentDirectionChangeTime--;
	}

	if (currentDirectionChangeTime == 0)
	{
		directionY = -directionY;
		currentDirectionChangeTime = directionChangeTime;
	}
}

void wormhole::draw()
{
	blit(texture, x, y);
}

int wormhole::getPositionX()
{
	return this->x;
}

int wormhole::getPositionY()
{
	return this->y;
}

int wormhole::getHeight()
{
	return this->height;
}

int wormhole::getWidth()
{
	return this->width;
}

void wormhole::spawnHole(int posX, int posY)
{
	x = posX;
	y = posY;
}

void wormhole::setPosition(int posX, int posY)
{
	x = posX;
	y = posY;
}
