#include "GameScene.h"
using namespace std;

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

	currentSpawnTimer = 300;
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

	initFonts();
	// Initialize any scene logic here

	for (int i = 0; i < 3; i++)
	{
		spawn();
	}

	SDL_QueryTexture(background, NULL, NULL, &width, &height);

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

}

void GameScene::update()
{
	Scene::update();

	spawnLogic();
	collisionLogic();

}

void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(1400, 300 + (rand() % 300));
	spawnedEnemies.push_back(enemy);
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
	
	
	boom->setPosition(enemy->getPositionX(), enemy->getPositionY());
	cout << boom->getX();
	this->addGameObject(boom);
	
	
}

void GameScene::spawnLogic()
{
	if (currentSpawnTimer > 0)
	{
		currentSpawnTimer--;

	}

	if (currentSpawnTimer <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			spawn();
		}

		currentSpawnTimer = spawnTime;
	}
}

void GameScene::collisionLogic()
{
	//Collision Logic
	for (int i = 0; i < objects.size(); i++)
	{
		//Cast to bullet
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);

		//Check if the cast was successful
		if (bullet != NULL)
		{
			//If the bullet is coming from the enemy side, check against the player
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision(
					player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()

				);

				if (collision == 1)
				{
					player->die();
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
		}
	}
}
