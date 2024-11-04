#include "GameScene.h"
using namespace std;

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

	currentSpawnTimer = 300;
	powerSpawnTime = 1000;
	currentPowerSpawnTimer = 1000;
	spawnTime = 300;


}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{

	int width = SCREEN_WIDTH;
	int height = SCREEN_HEIGHT;

	background = loadTexture("gfx/background.png");

	Scene::start();

	points = 0; 
	isPowerOnScreen = false;
	isBossAlive = false;


	initFonts();
	// Initialize any scene logic here

	for (int i = 0; i < 3; i++)
	{
		spawnEnemies();
	}


	SDL_QueryTexture(background, NULL, NULL, &width, &height);

	trishotSound = SoundManager::loadSound("sound/342749__rhodesmas__notification-01.ogg");
	trishotSound->volume = 10;
	rapidSound = SoundManager::loadSound("sound/rapidfire_sfx.ogg");

}

void GameScene::draw()
{

	blitScale(background, 0, 0, &width, &height, 3);

	Scene::draw();

	
	drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

	if (!player->getIsAlive())
	{
		drawText(SCREEN_WIDTH / 2, 600, 255, 0, 0, TEXT_CENTER, "GAME OVER!");
	}

	if (isBossAlive == true)
	{
		drawText(110, 45, 255, 255, 255, TEXT_CENTER, "BOSS HP: %01d", spawnedBosses[0]->getBossHP());
	}
}

void GameScene::update()
{


	Scene::update();
	if (points >= 10)
	{
		spawnTime = 200;
	}

	if (points >= 20)
	{
		spawnTime = 100;
	}

	spawnLogic();
	collisionLogic();
	

}

void GameScene::spawnEnemies()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(200 + (rand() % 500), -200);
	spawnedEnemies.push_back(enemy);

	
}

void GameScene::spawnPowers()
{
	PowerUp* power = new PowerUp();
	power->powerID = rand() % 2 + 1;

	power->start();

	this->addGameObject(power);

	power->setPosition(200 + (rand() % 500), -200);
	spawnedPowers.push_back(power);

	
}

void GameScene::spawnBoss()
{
	//spawning boss function
	Boss* boss = new Boss();
	this->addGameObject(boss);
	boss->setPlayerTarget(player);

	boss->setPosition(250, 40);
	spawnedBosses.push_back(boss);

}

void GameScene::despawnBoss(Boss* boss)
{
	int index = -1;
	for (int i = 0; i < spawnedBosses.size(); i++)
	{
		//if the pointer matches
		if (boss == spawnedBosses[i])
		{
			index = i;
			break;
		}
	}

	//if match is found
	if (index != -1)
	{
		spawnedBosses.erase(spawnedBosses.begin() + index);
		delete boss;
	}
}

void GameScene::despawnEnemy(Enemy* enemy)
{

	int index = -1;
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		//if the pointer matches
		if (enemy == spawnedEnemies[i])
		{
			index = i;
			break;
		}
	}

	//if match is found
	if (index != -1)
	{
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;
	}
}

void GameScene::explodeEnemy(Enemy* enemy)
{
	explosion* boom = new explosion();
	
	//finds position of the enemy
	boom->setPosition(enemy->getPositionX(), enemy->getPositionY());
	this->addGameObject(boom);
	
	
}

void GameScene::explodeBoss(Boss* boss)
{
	explosion* boom = new explosion();

	//finds position of the boss
	boom->setPosition(boss->getPositionX(), boss->getPositionY());
	this->addGameObject(boom);

}

void GameScene::explodePlayer()
{
	explosion* boom = new explosion();

	//finds position of the player
	boom->setPosition(player->getPositionX(), player->getPositionY());
	this->addGameObject(boom);


}

void GameScene::despawnPower(PowerUp* power)
{
	int index = -1;
	
	for (int i = 0; i < spawnedPowers.size(); i++)
	{
		//if the pointer matches
		if (power == spawnedPowers[i])
			{
				index = i;
				break;

			}
	}

	//if match is found
	if (index != -1)
	{
		spawnedPowers.erase(spawnedPowers.begin() + index);
		delete power;
		isPowerOnScreen = false;
	}
}

void GameScene::spawnLogic()
{
	//enemy memory management
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		if (spawnedEnemies[i]->getPositionY() > SCREEN_HEIGHT + 60 || isBossAlive == true)
		{
			Enemy* eraseEnemy = spawnedEnemies[i];
			spawnedEnemies.erase(spawnedEnemies.begin() + i);
			delete eraseEnemy;

			break;
		}
	}

	//spawning logic to stop spawning enemies when boss is on screen
	if (isBossAlive == false)
	{
		if (currentSpawnTimer > 0)
		{
			currentSpawnTimer--;

		}

		if (currentSpawnTimer <= 0)
		{
			for (int i = 0; i < 3; i++)
			{
				spawnEnemies();
			}

			currentSpawnTimer = spawnTime;
		}
	}
	
	//spawning boss logic
	if (points == 20 && isBossAlive == false)
	{
		isBossAlive = true;
		spawnBoss();
	}
	
	if (points == 50 && isBossAlive == false)
	{
		isBossAlive = true;
		spawnBoss();
	}

	//powerspawn timer logic
	if (currentPowerSpawnTimer > 0)
	{
		currentPowerSpawnTimer--;
	}

	if (currentPowerSpawnTimer <= 0)
	{
		

		for (int i = 0; i < 1; i++)
		{
			spawnPowers();
			
		}
		
		currentPowerSpawnTimer = powerSpawnTime;

		}
	
}

void GameScene::collisionLogic()
{
	//Collision Logic
	for (int i = 0; i < objects.size(); i++)
	{
		//Cast to bullet
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);

		//Cast to power
		PowerUp* power = dynamic_cast<PowerUp*>(objects[i]);

		//Cast to boss
		Boss* boss = dynamic_cast<Boss*>(objects[i]);

		//Check if the cast was successful

		if (power != NULL)
		{
			int collision = checkCollision(
				player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
				power->getPositionX(), power->getPositionY(), power->getWidth(), power->getHeight()

			);

			//ID 1 trishot powerup, ID 2 rapidfire powerup
			if (collision == 1)
			{
				if (power->powerID == 1)
				{
					SoundManager::playSound(trishotSound);

				}

				if (power->powerID == 2)
				{
					SoundManager::playSound(rapidSound);
				}

				player->poweredUp(power->getPowerID());
				despawnPower(power);
				player->powerUpTime = 300;
				break;
			}
		}
	
		if (bullet != NULL)
		{
			//If the bullet is coming from the enemy side, check against the player
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision(
					player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()

				);

				if (collision == 1 && player->getIsAlive())
				{
					player->die();
					explodePlayer();
					break;
				}
			}

			//If the bullet is coming from the player side, check against the enemy
			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision(
						currentEnemy->getPositionX(), currentEnemy->getPositionY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()

					);

					if (collision == 1)
					{
						explodeEnemy(currentEnemy);
						despawnEnemy(currentEnemy);
						
						points++;

						break;
					}
				}
			}

			//If the bullet is coming from the player side, check against the boss
			if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedBosses.size(); i++)
				{
					Boss* currentBoss = spawnedBosses[i];

					int collision = checkCollision(
						currentBoss->getPositionX(), currentBoss->getPositionY(), currentBoss->getWidth(), currentBoss->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()

					);

					if (collision == 1)
					{
						currentBoss->takeDamage();
						if (currentBoss->getBossHP() <= 0)
						{
							isBossAlive = false;
							explodeBoss(currentBoss);
							despawnBoss(currentBoss);
							points += 10;
						}
						
					}
				}
			}
		}
	}
}
