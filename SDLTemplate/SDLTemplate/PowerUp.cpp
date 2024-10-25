#include "PowerUp.h"
#include "draw.h"

void PowerUp::start()
{
	if (powerId == 1) {

	

	}

	if (powerId == 2) {

	rapidShotTexture = loadTexture("gfx/rapidshot.png");

	}

	triShotTexture = loadTexture("gfx/points.png");

	directionX = 1;
	directionY = 1;
	speed = 5;
	width = 0;
	height = 0;

	directionChangeTime = (rand() % 100) + 10; //Direction change every 3-8 seconds
	currentDirectionChangeTime = 0;

	SDL_QueryTexture(triShotTexture, NULL, NULL, &width, &height);
	SDL_QueryTexture(rapidShotTexture, NULL, NULL, &width, &height);

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
	blit(triShotTexture, x, y);
	blit(rapidShotTexture, x, y);
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




