#include "enemy.h"
#include "Scene.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	
}

void Enemy::start()
{ 
	//Load Texture
	texture = loadTexture("gfx/enemy.png");

	directionX = 1;
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

void Enemy::update()
{
	x += directionX * speed;
	y += directionY * speed;

	//random movement here
	if (currentDirectionChangeTime > 0)
	{
		currentDirectionChangeTime--;
	}

	//make sure enemies bounce on the sides of the screen
	if (currentDirectionChangeTime == 0 || x < 0 || x > SCREEN_WIDTH)
	{
		directionX = -directionX;
		currentDirectionChangeTime = directionChangeTime;
	}

	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}

	//alien aiming and firing
	if (currentReloadTime == 0 && y > 0 && playerTarget->getIsAlive())
	{
		float dx = -1;
		float dy = 0;

		calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + 3 + width / 2, y - 3 + height / 2, dx, dy, 10, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		bullet->start();

		currentReloadTime = reloadTime;
	}

	//memory management
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionY() < 0)
		{
			Bullet* bulletErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletErase;

			break;
		}
	}
}

void Enemy::draw()
{
	blit(texture, x, y);

}

void Enemy::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

void Enemy::setPosition(int posX, int posY)
{
	this->x = posX;
	this->y = posY;
}

int Enemy::getPositionX()
{
	return this->x;
}

int Enemy::getPositionY()
{
	return this->y;
}

int Enemy::getWidth()
{
	return this->width;
}

int Enemy::getHeight()
{
	return this->height;
}
