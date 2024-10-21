#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

enum class Side
{
	PLAYER_SIDE,
	ENEMY_SIDE
};
class Bullet : public GameObject
{
public:
	Bullet(float positionX, float positionY, float directionX, float directionY, float speed, Side side);
	void start();
	void update();
	void draw();

	float getPositionX();
	float getPositionY();
	float getWidth();
	float getHeight();

	Side getSide();

private:
	Side side;
	SDL_Texture* texture;
	int x;
	int y;
	int width;
	int height;
	int speed;
	float directionX;
	float directionY;

};

