#include "explosion.h"


void explosion::start()
{
	texture = loadTexture("gfx/explosion.png");

	width = 0;
	height = 0;

	despawnTime = 4;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	boom = SoundManager::loadSound("sound/245372__quaker540__hq-explosion.ogg");
	boom->volume = 10;

	SoundManager::playSound(boom);

}

void explosion::update()
{
	if (despawnTime > 0)
	{
		despawnTime--;
	}

	if (despawnTime == 0)
	{
		delete this;
	}
}

void explosion::draw()
{
	blit(texture, x, y);
}

void explosion::setPosition(int x, int y)
{
	 this->x = x;
	 this->y = y;
}

