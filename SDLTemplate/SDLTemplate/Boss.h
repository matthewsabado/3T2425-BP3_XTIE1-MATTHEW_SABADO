#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>
#include "util.h"
#include "Player.h"

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

    SDL_Texture* texture;
    Mix_Chunk* sound;
    vector<Bullet*> bullets;
    Player* playerTarget;

};

