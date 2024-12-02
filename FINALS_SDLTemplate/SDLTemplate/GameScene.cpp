#include "GameScene.h"


GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);
   
    gemObj = new gem();
    this->addGameObject(gemObj);

    wormObj = new wormhole();
    this->addGameObject(wormObj);

    isWin = false;
}

GameScene::~GameScene()
{
	delete player;


}

void GameScene::start()
{

    background = loadTexture("gfx/background.png");

    wormholeSFX = SoundManager::loadSound("sound/wormhole.mp3");
    gemSFX = SoundManager::loadSound("sound/YouWin.mp3");

    SoundManager::loadMusic("music/music.mp3");
    SoundManager::playMusic(-1);
    Mix_VolumeMusic(5);

    level = 1;
	Scene::start();

    initFonts();
	// Initialize any scene logic here
	
    SDL_QueryTexture(background, NULL, NULL, &width, &height);
}

void GameScene::draw()
{
    blitScale(background, 0, -6, &width, &height, 9);

	Scene::draw();
    
    if (!player->getDashCooldown() && textTimer >= 0)
    {
        drawText(SCREEN_WIDTH / 2, 50, 255, 255, 255, TEXT_CENTER, "!! DASH IS READY !!");
        
    }
    if (!player->getIsAlive())
    {
        drawText(SCREEN_WIDTH / 2, 600, 255, 0, 0, TEXT_CENTER, "GAME OVER!");
        drawText(SCREEN_WIDTH / 2, 630, 255, 0, 0, TEXT_CENTER, "PRESS R TO RESTART");
    }

    if (isWin)
    {
        drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 255, 0, TEXT_CENTER, "YOU WIN!!");
    }
}

void GameScene::update()
{
    if (textTimer > 0)
    {
        textTimer--;

    }

    if (textTimer < 0)
    {
        textTimer = 20;
    }

    if (!player->getIsAlive() && app.keyboard[SDL_SCANCODE_R])
    {
        restartGame();
    }

    //level debugging
    if (app.keyboard[SDL_SCANCODE_N])
    {
        level = 1;
    }

    if (app.keyboard[SDL_SCANCODE_M])
    {
        level = 2;
    }

    loadLevel(level);

	Scene::update();
	collisionLogic();

}

void GameScene::loadLevel(int currentLevel)
{
    for (auto& spikyball : spikyballs)
    {
        delete spikyball;
    }

    spikyballs.clear();

    for (auto& platform : platforms)
    {
        delete platform;
    }

    platforms.clear();

    //level 1
    if (level == 1)
    {
        wormObj->spawnHole(200, 200);
        wormObj->setPosition(601, 60);

        // {X position, Y position}
        vector<pair<int, int>> spikyBallPositions
        { {400, 623}, {401, 493}, {351, 431}, 
            {451, 431}, {401, 377}, {401, 427},
            {71, 273}, {71, 223}, {441, 203} };

        vector<pair<int, int>> platformPositions
        { {90, 670}, {250, 600}, {528, 605}, 
            {731, 515}, {561, 463}, {141, 452}, {21, 403}, 
            {711, 355}, {260, 313}, {131, 273},
            {291, 223}, {451, 183}, {491, 313} };

        //for creating multiple balls
        for (const auto& pos : spikyBallPositions)
        {
            obstacles* newSpikyBall = new obstacles();

            newSpikyBall->spawn(pos.first, pos.second);
            spikyballs.push_back(newSpikyBall);
            this->addGameObject(newSpikyBall);
        }

        for (const auto& pos : platformPositions)
        {
            
            Platform* newPlatform = new Platform();

            newPlatform->spawn(pos.first, pos.second);
            platforms.push_back(newPlatform);
            this->addGameObject(newPlatform);
        }

        gemObj->setPosition(-100, -100);
    }

    //level 2
    if (level == 2)
    {

        gemObj->spawnGem(200, 200);
        gemObj->setPosition(-5, 50);

        vector<pair<int, int>> spikyBallPositions
        { {455, 523}, { 685, 623 }, {735, 593}, 
            {785, 623}, {735, 643},{145, 533}, 
            {325, 483}, {515, 383},{615, 383}, 
            {785, 303}, {295, 253}, {415, 243},  
            {475, 163}, {295, 133}, {295, 323}, {131, 383} };

        vector<pair<int, int>> platformPositions
        { {95, 663}, {285, 613}, {555, 633}, 
            {25, 563}, {205, 519}, {395, 483}, 
            {675, 485}, {19, 449}, 
            {15, 363}, {175, 313}, {355, 353}, 
            {535, 313}, {695, 263}, {535, 213}, 
            {185, 153}, {85, 153}, {-15, 153} };

        //for creating multiple balls
        for (const auto& pos : spikyBallPositions)
        {
            obstacles* newSpikyBall = new obstacles();

            newSpikyBall->spawn(pos.first, pos.second);
            spikyballs.push_back(newSpikyBall);
            this->addGameObject(newSpikyBall);
        }

        for (const auto& pos : platformPositions)
        {
            Platform* newPlatform = new Platform();

            newPlatform->spawn(pos.first, pos.second);
            platforms.push_back(newPlatform);
            this->addGameObject(newPlatform);
        }

        wormObj->setPosition(-100, -100);
    }
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

        //cast to gem
        gem* gemObj = dynamic_cast<gem*>(objects[i]);

        //cast to wormhole
        wormhole* wormObj = dynamic_cast<wormhole*>(objects[i]);

        //platform collision
        if (platform != NULL)
        {
            int collision = checkCollision(
                player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
                platform->getPositionX(), platform->getPositionY(), platform->getWidth(), platform->getHeight()
            );

            if (collision == 1)
            {
                if (player->getVelocity() > 0)
                {
                   
                    float playerBottom = player->getPositionY() + player->getHeight();
                    float platformTop = platform->getPositionY();

                    

                        if (player->getVelocity() > 10 || playerBottom > platformTop && playerBottom - platformTop < 5.0f)
                        {
               
                            player->setPositionY(platformTop - player->getHeight());
                            player->setVelocity(0);
                            player->setIsGrounded(true);

                        }
                    
                }

                break;
            }
        }
        
        //spikyball collission
        if (spikyball != NULL) {
            int collision = checkCollision(
                player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
                spikyball->getPositionX(), spikyball->getPositionY(), spikyball->getWidth(), spikyball->getHeight()
            );

            if (collision == 1 && player->getIsAlive())
            {
                player->die();
                playerBoom();
                break;

            }
        }

        if (gemObj != NULL) {
            int collision = checkCollision(
                player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
                gemObj->getPositionX(), gemObj->getPositionY(), gemObj->getWidth(), gemObj->getHeight()
            );

            if (collision == 1 && player->getIsAlive())
            {
                SoundManager::playSound(gemSFX);
                gemSFX->volume = 30;

                isWin = true;
                delete gemObj;
                break;

            }
        }

        if (wormObj != NULL) {
            int collision = checkCollision(
                player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
                wormObj->getPositionX(), wormObj->getPositionY(), wormObj->getWidth(), wormObj->getHeight()
            );

            if (collision == 1 && player->getIsAlive())
            {
                SoundManager::playSound(wormholeSFX);
                

                level++;
                loadLevel(level);
                player->setPositionX(SCREEN_WIDTH / 2);
                player->setPositionY(750);
                break;

            }
        }
    }
}

void GameScene::playerBoom()
{
    deathExplosion* boom = new deathExplosion();

    //finds position of the player
    boom->setPosition(player->getPositionX(), player->getPositionY());
    this->addGameObject(boom);

}

void GameScene::restartGame()
{
    player->revive();
    player->setPositionX(SCREEN_WIDTH / 2);
    player->setPositionY(800);
    player->setVelocity(0);
    player->setIsGrounded(true);

    loadLevel(level);
}


