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

	bossHealth = 10000;
	directionX = 1;
	directionY = 0;
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 50;
	currentReloadTime = 0;
	directionChangeTime = 100; //Direction change every 3-8 seconds
	currentDirectionChangeTime = 0;
	isBossInPlace = false;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);


	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 64;


}

void Boss::update()
{


	if (isBossOnScreen == true)
	{
		drawText(110, 20, 255, 255, 255, TEXT_CENTER, "BOSS HP: ", bossHealth);
	}

	x += directionX * speed;
	y += directionY * speed;

	//random movement here
	if (currentDirectionChangeTime > 0)
	{
		currentDirectionChangeTime--;
		
	}

	//make sure boss bounces on the sides of the screen
	if (currentDirectionChangeTime == 0 || x < 0 || x > SCREEN_WIDTH)
	{
		directionX = -directionX;
		currentDirectionChangeTime = directionChangeTime;

	}

	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}

	if (currentReloadTime == 0 && y == 40 && playerTarget->getIsAlive())
	{
		float dy = 1;

		SoundManager::playSound(sound);
		Bullet* leftbullet1 = new Bullet(x + 5 + width / 2, y + 3 + height / 2, 0.6, dy, 10, Side::ENEMY_SIDE);
		Bullet* leftbullet2 = new Bullet(x + 5 + width / 2, y + 3 + height / 2, 0.15, dy, 10, Side::ENEMY_SIDE);
		Bullet* rightbullet3 = new Bullet(x + 5 + width / 2, y + 3 + height / 2, -0.6, dy, 10, Side::ENEMY_SIDE);
		Bullet* rightbullet4 = new Bullet(x + 5 + width / 2, y + 3 + height / 2, -0.15, dy, 10, Side::ENEMY_SIDE);
		bullets.push_back(leftbullet1);
		bullets.push_back(leftbullet2);
		bullets.push_back(rightbullet3);
		bullets.push_back(rightbullet4);
		getScene()->addGameObject(leftbullet1);
		getScene()->addGameObject(leftbullet2);
		getScene()->addGameObject(rightbullet3);
		getScene()->addGameObject(rightbullet4);
		leftbullet1->start();
		leftbullet2->start();
		rightbullet3->start();
		rightbullet4->start();

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

int Boss::getBossHP()
{
	return this->bossHealth;
}

void Boss::takeDamage()
{
	bossHealth -= 1;
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
