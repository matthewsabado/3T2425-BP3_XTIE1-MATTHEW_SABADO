#include "Player.h"
#include "Scene.h"

Player::~Player()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}

	bullets.clear();
}

void Player::start()
{
	//Load Texture
	texture = loadTexture("gfx/player.png");

	x = SCREEN_WIDTH / 2 - 24;
	y = 750;
	width = 0;
	height = 0;
	mainReloadTime = 10;
	sideReloadTime = 30;

	speed = baseSpeed;

	isAlive = true;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Player::update()
{
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

	if (!isAlive) return;

	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		speed = 5;
	}

	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		speed = baseSpeed;
	}

	if (app.keyboard[SDL_SCANCODE_UP]) 
	{
		y -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_DOWN]) 
	{
		y += speed;
	}

	if (app.keyboard[SDL_SCANCODE_LEFT])
	{
		x -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_RIGHT]) 
	{
		x += speed;
	}

	if (currentMainReloadTime > 0)
	{
		currentMainReloadTime--;
	}

	if (currentSideReloadTime > 0)
	{
		currentSideReloadTime--;
	}

	if (app.keyboard[SDL_SCANCODE_F] && currentMainReloadTime == 0) 
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x - 5 + width / 2, y - 20 + height / 2, 0, -1, 10, Side::PLAYER_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		bullet->start();

		currentMainReloadTime = mainReloadTime;
	}

	if (app.keyboard[SDL_SCANCODE_G] && currentSideReloadTime == 0)
	{
		powerUp1();
	 }

}


void Player::draw()
{
	if (!isAlive) return;

	blit(texture, x, y);
}

int Player::getPositionX()
{
	return this->x;
}

int Player::getPositionY()
{
	return this->y;
}

int Player::getWidth()
{
	return this->width;
}

int Player::getHeight()
{
	return this->height;
}

bool Player::getIsAlive()
{
	return isAlive;
}

void Player::die()
{
	isAlive = false;
}

void Player::powerUp1()
{

	SoundManager::playSound(sound);
	Bullet* leftBullet = new Bullet(x - 25 + width / 2, y - 10 + height / 2, -0.125, -1, 10, Side::PLAYER_SIDE);
	Bullet* rightBullet = new Bullet(x + 18 + width / 2, y - 10 + height / 2, 0.25, -1, 10, Side::PLAYER_SIDE);
	bullets.push_back(leftBullet);
	bullets.push_back(rightBullet);
	getScene()->addGameObject(leftBullet);
	getScene()->addGameObject(rightBullet);
	leftBullet->start();
	rightBullet->start();

	currentSideReloadTime = sideReloadTime;
}


