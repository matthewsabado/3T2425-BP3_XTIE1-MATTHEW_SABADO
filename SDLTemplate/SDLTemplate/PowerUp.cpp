#include "PowerUp.h"
#include "draw.h"

void PowerUp::start()
{

	//loading trishot texture
	if (powerID == 1)
	{
		texture = loadTexture("gfx/points.png");
	}

	//loading rapidshot texture

	else if (powerID == 2)
	{
		texture = loadTexture("gfx/rapidfire.png");
	}

	directionX = 1;
	directionY = 1;
	speed = 5;
	width = 0;
	height = 0;

	directionChangeTime = (rand() % 100) + 10; //random direction changing
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

	//make sure powerups bounce on the sides of the screen
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

int PowerUp::getPowerID()
{
	return this->powerID;
}





