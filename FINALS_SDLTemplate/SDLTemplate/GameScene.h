#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Platform.h"
#include "util.h"
#include "obstacles.h"
using namespace std;

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();

	void collisionLogic();

private:

	Player* player;
	Platform* platform;
	obstacles* spikyball;
	obstacles* spikes;

	vector<obstacles*> spikyballs;
	vector<Platform*> platforms;

};

