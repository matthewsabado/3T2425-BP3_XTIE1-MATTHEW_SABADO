#include "obstacles.h"

void obstacles::start()
{
	texture = loadTexture("gfx/spikyball.png");

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void obstacles::update()
{
}

void obstacles::draw()
{
	blit(texture, x, y);
}

int obstacles::getPositionX()
{
	return this->x;
}

int obstacles::getPositionY()
{
	return this->y;
}

int obstacles::getWidth()
{
	return this->width;
}

int obstacles::getHeight()
{
	return this->height;
}

void obstacles::spawn(int posX, int posY)
{
	x = posX;
	y = posY;
}

