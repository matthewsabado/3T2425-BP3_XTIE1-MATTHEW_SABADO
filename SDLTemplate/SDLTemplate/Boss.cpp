#include "Boss.h"

Boss::Boss()
{

}

Boss::~Boss()
{
}

void Boss::start()
{
	//Load Texture
	texture = loadTexture("gfx/bossPlaceholder.png");

	directionX = 0;
	directionY = 1;
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 60;
	currentReloadTime = 0;
	directionChangeTime = (rand() % 100) + 100; //Direction change every 3-8 seconds
	currentDirectionChangeTime = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 64;
}

void Boss::update()
{
	x += directionX * speed;
	y += directionY * speed;
}

void Boss::draw()
{
	blit(texture, x, y);
}

int Boss::getPositionX()
{
	return this->x;
}

int Boss::getPositionY()
{
	return this->y;
}

int Boss::getHeight()
{
	return this->height;
}

int Boss::getWidth()
{
	return this->width;
}

void Boss::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

void Boss::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}
