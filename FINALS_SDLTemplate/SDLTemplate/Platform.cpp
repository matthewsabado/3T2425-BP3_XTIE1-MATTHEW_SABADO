#include "Platform.h"

void Platform::start()
{
	texture = loadTexture("gfx/platform.png");

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Platform::update()
{
	
}

void Platform::draw()
{
	blit(texture, x, y);
}

int Platform::getPositionX()
{
	return this->x;
}

int Platform::getPositionY()
{
	return this->y;
}

int Platform::getWidth()
{
	return this->width;
}

int Platform::getHeight()
{
	return this->height;
}

void Platform::spawn(int posX, int posY)
{
	x = posX;
	y = posY;
}
