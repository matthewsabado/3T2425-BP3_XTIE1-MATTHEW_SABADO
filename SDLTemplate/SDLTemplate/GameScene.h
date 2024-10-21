#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "enemy.h"
#include "text.h"
#include "explosion.h"
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

	int points;

	void spawn();
	void despawnEnemy(Enemy* enemy);
	void explodeEnemy(Enemy* enemy);

	void spawnLogic();
	void collisionLogic();
};

