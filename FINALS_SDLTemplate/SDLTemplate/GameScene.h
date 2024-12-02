#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Platform.h"
#include "util.h"
#include "obstacles.h"
#include "deathExplosion.h"
#include "SDL_mixer.h"
#include "text.h"
#include "gem.h"
#include "wormhole.h"

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
	int level;
	int width;
	int height;
	int textTimer;
	bool isWin;

	Player* player;
	Platform* platform;
	obstacles* spikyball;

	gem* gemObj;
	wormhole* wormObj;

	vector<obstacles*> spikyballs;
	vector<Platform*> platforms;

	void loadLevel(int currentLevel);
	void collisionLogic();
	void playerBoom();
	void restartGame();


	SDL_Texture* background;

	Mix_Chunk* gemSFX;
	Mix_Chunk* wormholeSFX;
};

