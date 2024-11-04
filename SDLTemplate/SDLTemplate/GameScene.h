#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "enemy.h"
#include "text.h"
#include "explosion.h"
#include "PowerUp.h"
#include "Boss.h"
#include <vector>
using namespace std;

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
private:
	int width;
	int height;
	Player* player;
	Enemy* enemy;
	SDL_Texture* background;

	//enemy spawning
	float spawnTime;
	float currentSpawnTimer;
	
	vector<Enemy*> spawnedEnemies;
	vector<PowerUp*> spawnedPowers;
	vector<Boss*> spawnedBosses;
	Mix_Chunk* trishotSound;
	Mix_Chunk* rapidSound;

	int points;

	bool isPowerOnScreen;
	int powerSpawnTime;
	float currentPowerSpawnTimer;


	bool isBossAlive;

	void spawnEnemies();
	void spawnPowers();

	void spawnBoss();
	void despawnBoss(Boss* boss);
	void despawnEnemy(Enemy* enemy);
	void explodeEnemy(Enemy* enemy);
	void explodeBoss(Boss* boss);
	void explodePlayer();
	void despawnPower(PowerUp* power);

	void spawnLogic();
	void collisionLogic();
};

