#pragma once
#include "GameObject.h"
#include "Scene.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>
#include "util.h"
#include "Player.h"
#include "text.h"

class Boss : public GameObject
{
public:
    Boss();
    ~Boss();
    void start();
    void update();
    void draw();

    int getPositionX();
    int getPositionY();
    int getHeight();
    int getWidth();

    int getBossHP();

    void takeDamage();

    void setPlayerTarget(Player* player);
    void setPosition(int x, int y);

private:
    int x;
    int y;
    int directionX;
    int directionY;
    int width;
    int height;
    int speed;
    int bossHealth;
  
    float reloadTime;
    float currentReloadTime;
    float directionChangeTime;
    float currentDirectionChangeTime;
    int firingPattern;
    bool isBossOnScreen;
    int patternChangeTimer;
    void changeFiringPatterns(int pattern);

    SDL_Texture* texture;
    Mix_Chunk* sound;
    vector<Bullet*> bullets;
    Player* playerTarget;

};

