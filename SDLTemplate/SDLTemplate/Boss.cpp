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
	texture = loadTexture("gfx/boss.png");

	bossHealth = 500;
	directionX = 1;
	directionY = 0;
	width = 0;
	height = 0;
	speed = 5;
	reloadTime = 30;
	currentReloadTime = 0;
	directionChangeTime = 500; 
	currentDirectionChangeTime = 0;
	patternChangeTimer = 300;
	firingPattern = rand() % 3;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);


	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 64;


}

void Boss::update()
{

	if (isBossOnScreen == true)
	{
		drawText(50, 20, 255, 255, 255, TEXT_CENTER, "BOSS HP: ", bossHealth);
	}

	x += directionX * speed;
	y += directionY * speed;

	//random movement here
	if (currentDirectionChangeTime > 0)
	{
		currentDirectionChangeTime--;
		
	}

	//make sure boss bounces on the sides of the screen
	if (currentDirectionChangeTime == 0 || x < 0 || x > 625)
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

		changeFiringPatterns(firingPattern);
		
		
		
		
		
		currentReloadTime = reloadTime;
		
	}

	patternChangeTimer--;

	if (patternChangeTimer <= 0)
	{
		cout << "Current pattern: " << firingPattern << endl;
		firingPattern = rand() % 3;
		patternChangeTimer = 300;
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
	bossHealth--;
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

void Boss::changeFiringPatterns(int pattern)
{
	float dy = 1;
	float dx = 1;

	// firing pattern 1: spread
	if (pattern == 0)
	{
		reloadTime = 30;
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
	}

	//firing pattern 2: slow bullets
	if (pattern == 1)
	{
		reloadTime = 20;
		SoundManager::playSound(sound);
		Bullet* bullet1 = new Bullet(x + 5 + width / 2, y + 3 + height / 2, 0, dy, 5, Side::ENEMY_SIDE);
		Bullet* bullet2 = new Bullet(x - 5 + width / 2, y + 3 + height / 2, 0, dy, 5, Side::ENEMY_SIDE);
		getScene()->addGameObject(bullet1);
		getScene()->addGameObject(bullet2);
		bullet1->start();
		bullet2->start();

	}

	//firing pattern 3: tracking
	if (pattern == 2)
	{
		reloadTime = 30;
		calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + 3 + width / 2, y - 3 + height / 2, dx, dy, 10, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		bullet->start();
	}
}
