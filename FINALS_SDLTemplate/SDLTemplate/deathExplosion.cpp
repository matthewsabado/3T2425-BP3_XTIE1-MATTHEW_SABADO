#include "deathExplosion.h"

void deathExplosion::start()
{
	texture = loadTexture("gfx/explosion.png");

	width = 0;
	height = 0;

	despawnTime = 10;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	boom = SoundManager::loadSound("sound/death.wav");
	boom->volume = 10;

	SoundManager::playSound(boom);

}

void deathExplosion::update()
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

void deathExplosion::draw()
{
	blit(texture, x, y);

}

void deathExplosion::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}
