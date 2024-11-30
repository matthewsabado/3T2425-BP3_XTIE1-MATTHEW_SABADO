#include "GameScene.h"


GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

	platform = new Platform();
	this->addGameObject(platform);

    const int numOfBalls = 20;
    const int numOfPlatforms = 40;

    //for creating multiple balls
    for (int i = 0; i < numOfBalls; i++)
    {
        obstacles* newSpikyBall = new obstacles();
        spikyballs.push_back(newSpikyBall);
        this->addGameObject(newSpikyBall);
    }

    for (int i = 0; i < numOfPlatforms; i++)
    {
        Platform* newPlatform = new Platform();
        platforms.push_back(newPlatform);
        this->addGameObject(newPlatform);
    }

    
}

GameScene::~GameScene()
{
	delete player;

    for (auto& spikyball : spikyballs)
    {
        delete spikyball;
    }

}

void GameScene::start()
{
    //level 1
    spikyballs[0]->spawn(200, 700);
    spikyballs[1]->spawn(100, 600);

    platforms[0]->spawn(400, 650);
    platforms[1]->spawn(200, 500);

	Scene::start();
	// Initialize any scene logic here
	
	
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();
	collisionLogic();
}

void GameScene::collisionLogic()
{
    //Collision Logic
    for (int i = 0; i < objects.size(); i++)
    {

        // Cast to platform
        Platform* platform = dynamic_cast<Platform*>(objects[i]);

        //cast to spiky ball
        obstacles* spikyball = dynamic_cast<obstacles*>(objects[i]);

        if (platform != NULL)
        {
            int collision = checkCollision(
                player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
                platform->getPositionX(), platform->getPositionY(), platform->getWidth(), platform->getHeight()
            );

            if (collision == 1)
            {
                if (player->getVelocity() >= 0)
                {

                        player->setIsGrounded(true);

                        if (player->getPositionY() + player->getHeight() > platform->getPositionY() - 10)
                        {
                            player->setPositionY(platform->getPositionY() - player->getHeight());
                            player->setVelocity(0);
                        }
                    
                }
            }
        }

        if (spikyball != NULL) {
            int collision = checkCollision(
                player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
                spikyball->getPositionX(), spikyball->getPositionY(), spikyball->getWidth(), spikyball->getHeight()
            );

            if (collision == 1)
            {
                cout << "balls";

            }
        }
    }
}


