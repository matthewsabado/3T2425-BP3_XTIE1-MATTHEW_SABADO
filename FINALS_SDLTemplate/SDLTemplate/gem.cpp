#include "gem.h"
using namespace std;

void gem::start()
{
	texture = loadTexture("gfx/gem.png");
	speed = 1;
	directionY = 1;
	directionChangeTime = 25;
	currentDirectionChangeTime = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void gem::update()
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

void gem::draw()
{
	blit(texture, x, y);
}

int gem::getPositionX()
{
	return this->x;
}

int gem::getPositionY()
{
	return this->y;
}

int gem::getHeight()
{
	return this->height;
}

int gem::getWidth()
{
	return this->width;
}

void gem::spawnGem(int posX, int posY)
{
	y = posY;
	x = posX;
}

void gem::setPosition(int posX, int posY)
{
	x = posX;
	y = posY;
}

