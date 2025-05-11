#include "game.h"
#include <cstdlib>
#include <ctime>


// Initialize variables
void game::initVariable()
{
    /*this->window = nullptr;*/
    game::intitSprite();
    this->player.initPlayer();
    initAudio();
    cout << "init works\n";


    if (!introBackgroundTexture.loadFromFile("Asset/Introbackground 2.png")) {
        cout << "Failed to load intro background!\n";
    }

    // Load font
    if (!font.loadFromFile("Asset/ARIALNI.ttf")) {
        cout << "Failed to load font!\n";
    }



    introBackgroundSprite.setTexture(introBackgroundTexture);
    introBackgroundSprite.setScale(2.0, 2.0);

    // Game title
    titleText.setFont(font);
    titleText.setCharacterSize(48);
    titleText.setFillColor(Color::White);
    titleText.setString("Galactic Recoil");
    titleText.setPosition(window->getSize().x / 2.7f, 170.f);

    healthBarBg.setSize(Vector2f(200.f, 20.f));
    healthBarBg.setFillColor(Color::Red);
    healthBarBg.setPosition(20.f, 20.f);

    healthBar.setSize(Vector2f(200.f, 20.f));
    healthBar.setFillColor(Color::Green);
    healthBar.setPosition(20.f, 20.f);


    // Game Over title
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(54);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setString("Game Over");
    gameOverText.setPosition(window->getSize().x / 2.5f, 150.f);

    // Play Again button
    playAgainButton.setSize(Vector2f(200.f, 50.f));
    playAgainButton.setPosition(412.f, 300.f);
    playAgainButton.setFillColor(Color::Green);

    playAgainText.setFont(font);
    playAgainText.setCharacterSize(24);
    playAgainText.setFillColor(Color::Black);
    playAgainText.setString("Play Again");


    playAgainText.setPosition(470.f, 312.f);


    score = 0;


    // Score Text setup
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(20.f, 50.f);
    scoreText.setString("Score: 0");

    // Health Label inside the bar
    healthLabel.setFont(font);
    healthLabel.setCharacterSize(18);
    healthLabel.setFillColor(Color::Black);
    healthLabel.setPosition(25.f, 22.f);
    healthLabel.setString("Health");

    // Play button
    playButton.setSize(Vector2f(200.f, 50.f));
    playButton.setPosition(412.f, 300.f);
    playButton.setFillColor(Color::Green);

    playText.setFont(font);
    playText.setCharacterSize(24);
    playText.setFillColor(Color::Black);
    playText.setString("Play");
    playText.setPosition(492.f, 312.f);

    // Time trial variable
    isTimeTrialActive = false;
    timeTrialTimer = 0.f;
    timeTrialTarget = 0;
    timeTrialKills = 0;
    

    // time trial result
    showTimeTrialResult = false;

    timeTrialResultText.setFont(font);
    timeTrialResultText.setCharacterSize(36);
    timeTrialResultText.setFillColor(Color::White);
    timeTrialResultText.setPosition(300.f, 250.f);

    continueButton.setSize(Vector2f(200.f, 50.f));
    continueButton.setPosition(window->getSize().x / 2.0f - 100.f, window->getSize().y / 2.0f + 50.f);
    continueButton.setFillColor(Color::Blue);

    continueText.setFont(font);
    continueText.setCharacterSize(24);
    continueText.setFillColor(Color::White);
    continueText.setString("Continue");

    // Center the continue text on the button
    FloatRect textRect = continueText.getLocalBounds();
    continueText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    continueText.setPosition(continueButton.getPosition().x + continueButton.getSize().x / 2.0f,
        continueButton.getPosition().y + continueButton.getSize().y / 2.0f);



    // Exit button
    exitButton.setSize(Vector2f(200.f, 50.f));
    exitButton.setPosition(412.f, 370.f);
    exitButton.setFillColor(Color::Red);

    exitText.setFont(font);
    exitText.setCharacterSize(24);
    exitText.setFillColor(Color::Black);
    exitText.setString("Exit");
    exitText.setPosition(492.f, 382.f);

    isGameOver = false;
    inIntroScreen = true;
    isShooting = false;


}

// Initialize the window
void game::intitWindow()
{
    this->window = new RenderWindow(VideoMode(1024, 768), "Adventure Game");
    this->window->setFramerateLimit(60);
}

// Initialize the map sprite
void game::intitSprite()
{
    if (this->mapT.loadFromFile("Asset/background.png") == false) return;

    mapT.setRepeated(true);
    this->map.setTexture(mapT);
    map.setScale(1.f, 1.f);
}

// Constructor
game::game()
{
    game::intitWindow();
    game::initVariable();
    
}

// Destructor
game::~game()
{
    shootSound.stop();
    backgroundMusic.stop();
    delete this->window;
}


// Check if the window is open
bool game::iswindowopen() const
{
    return this->window->isOpen();
}



void game::startTimeTrial(float duration, int targetKills)
{
    isTimeTrialActive = true;
    timeTrialTimer = duration;
    timeTrialTarget = targetKills;
    timeTrialKills = 0;
}

void game::initAudio()
{
    musicVolume = 50.f;
    sfxVolume = 70.f;

    // Load shooting sound
    if (!shootBuffer.loadFromFile("Asset/shoot.wav")) {
        cout << "Failed to load shooting sound!" << endl;
    }
    shootSound.setBuffer(shootBuffer);
    shootSound.setVolume(sfxVolume);

    if (!backgroundMusic.openFromFile("Asset/game_music.ogg")) {
        cout << "Failed to load background music!" << endl;
    }
    backgroundMusic.setVolume(musicVolume);
    backgroundMusic.setLoop(true);

    backgroundMusic.play();
}

void game::playSound(Sound& sound)
{
    sound.setVolume(sfxVolume);
    sound.play();
}

// Poll events
void game::pollEvent()
{
    while (this->window->pollEvent(this->event))
    {
        if (this->event.type == Event::Closed)
        {
            this->window->close();
        }

        if (inIntroScreen && event.type == Event::MouseButtonPressed)
        {
            Vector2f mousePos = window->mapPixelToCoords(Mouse::getPosition(*window));
            if (playButton.getGlobalBounds().contains(mousePos)) 
            {
                inIntroScreen = false;
                startTimeTrial(60.f, 50);
            }
            else if (exitButton.getGlobalBounds().contains(mousePos))
            {
                window->close();
            }
        }
        else if (isGameOver && event.type == Event::MouseButtonPressed)
        {
            Vector2f mousePos = window->mapPixelToCoords(Mouse::getPosition(*window));
            if (playAgainButton.getGlobalBounds().contains(mousePos))
            {
                // reset game
                enemies.clear();
                bullets.clear();
                score = 0;
                player.reset();
                maxEnemies = 5;
                spawnInterval = 2.0f;
                inIntroScreen = false;
                isGameOver = false;


                isTimeTrialActive = false;
                timeTrialTimer = 0.f;
                timeTrialKills = 0;
                showTimeTrialResult = false;

                startTimeTrial(60.f, 50);
            }
            else if (exitButton.getGlobalBounds().contains(mousePos))
            {
                window->close();
            }
        }

        else if (showTimeTrialResult && event.type == Event::MouseButtonPressed)
        {
            Vector2f mousePos = window->mapPixelToCoords(Mouse::getPosition(*window));
            if (continueButton.getGlobalBounds().contains(mousePos))
            {
                showTimeTrialResult = false;
                
                isGameOver = true;
            }
        }
    }
}


void game::PlayerMotion()
{
    // Player Movement Logic
    float moveX = 0.f, moveY = 0.f;
    bool isMoving = false;

    Vector2f playerPos = this->player.getPosition();
    Vector2u windowSize = this->window->getSize();

    if (Keyboard::isKeyPressed(Keyboard::W) && playerPos.y > 0)
    {
        moveY = -5.f;
        isMoving = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::A) && playerPos.x > 0)
    {
        moveX = -5.f;
        isMoving = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::S) && playerPos.y < windowSize.y - this->player.getSize().y)
    {
        moveY = 5.f;
        isMoving = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::D) && playerPos.x < windowSize.x - this->player.getSize().x)
    {
        moveX = 5.f;
        isMoving = true;
    }
    this->player.updatePosition(moveX, moveY);
    this->player.updateHealth(0.016f);


    if (isMoving)
        this->player.updateAnimation(0.016f);
    else
        this->player.setStaticFrame();
}

void game::Shooting()
{
    if (Mouse::isButtonPressed(Mouse::Left)) {
        if (!isShooting) {
            isShooting = true; 

            Vector2f playerCenter = player.getPosition() + player.getSize() / 2.f;
            Vector2i mousePosScreen = Mouse::getPosition(*this->window);
            Vector2f mousePosWorld = this->window->mapPixelToCoords(mousePosScreen);

            bullets.emplace_back(playerCenter, mousePosWorld); 
            playSound(shootSound);

        }
    }
    else {
        isShooting = false; 
    }
}

void game::bulletEnemyCollision()
{
    for (int i = 0; i < bullets.size(); ) {
        bool bulletRemoved = false;

        for (int j = 0; j < enemies.size() && !bulletRemoved; ) {
            if (bullets[i].getBounds().intersects(enemies[j].getBounds()))
            {

                bullets.erase(bullets.begin() + i);
                enemies.erase(enemies.begin() + j);
                score++;
                if (isTimeTrialActive)
                {
                    timeTrialKills++;
                }


                scoreText.setString("Score: " + to_string(score));
                bulletRemoved = true;
            }
            else 
            {
                ++j;
            }
        }

        if (!bulletRemoved) ++i;
    }
}

void game::SpawnEnemy()
{
    spawnTimer += 0.016f;
    difficultyTimer += 0.016f;
    enemyCapTimer += 0.016f;
    if (spawnTimer >= spawnInterval && enemies.size() < maxEnemies) {
        spawnTimer = 0.f;

        Enemy enemy;
        float randX = static_cast<float>(rand() % 900 + 50);
        float randY = static_cast<float>(rand() % 600 + 50);
        enemy.setPosition(Vector2f(randX, randY));

        enemies.push_back(enemy);
    }

    if (difficultyTimer >= 6.f) {
        difficultyTimer = 0.f;
        if (spawnInterval > spawnIntervalMin)
            spawnInterval -= 0.2f;
    }

    if (enemyCapTimer >= 7.f) {
        enemyCapTimer = 0.f;
        if (maxEnemies < maxAllowedEnemies)
            maxEnemies += 2;
    }



    for (auto& enemy : enemies) {
        enemy.update(player.getPosition());

        // player damage
        if (enemy.getBounds().intersects(FloatRect(player.getPosition(), player.getSize())))
        {
            player.takeDamage(5);

            // enemy bounce away after hitting the player
            Vector2f pushDir = enemy.getPosition() - player.getPosition();
            float len = sqrt(pushDir.x * pushDir.x + pushDir.y * pushDir.y);
            if (len != 0)
            {
                pushDir /= len;
                enemy.setPosition(enemy.getPosition() + pushDir * 100.f);
            }
            cout << "Player health: " << player.getHealth() << endl;
        }
    }
}

void game::updatingBullet()
{
    for (int i = 0; i < bullets.size(); ) {
        bullets[i].update();

        FloatRect bounds = bullets[i].getBounds();
        if (bounds.left + bounds.width < 0 || bounds.left > window->getSize().x ||
            bounds.top + bounds.height < 0 || bounds.top > window->getSize().y)
        {
            bullets.erase(bullets.begin() + i);
        }
        else {
            ++i;
        }
    }
}

void game::gameEndCheck()
{
    if (!player.isAlive()) {
        cout << "Game Over! Player has died." << endl;
        cout << "Player Score: " << score << endl;

        isTimeTrialActive = false;
        timeTrialTimer = 0.f;
        timeTrialKills = 0;

        showTimeTrialResult = true;
        timeTrialResultText.setString("Time Trial Failed!\nYou died before completing the trial.");
        timeTrialResultText.setFillColor(Color::Red);

        return;
    }
}

void game::timeTrial()
{
    if (isTimeTrialActive) {
        timeTrialTimer -= 0.016f; 

        if (timeTrialKills >= timeTrialTarget) {
            isTimeTrialActive = false;
            showTimeTrialResult = true;
            timeTrialResultText.setString("Time Trial Complete!\nYou killed " + to_string(timeTrialKills) +
                " enemies in " + to_string(static_cast<int>(60.f - timeTrialTimer)) + " seconds!");
            timeTrialResultText.setFillColor(Color::Green);
        }
        else if (timeTrialTimer <= 0.f) {
            isTimeTrialActive = false;
            showTimeTrialResult = true;
            timeTrialResultText.setString("Time Trial Failed!\nYou killed " + to_string(timeTrialKills) +
                " out of " + to_string(timeTrialTarget) + " enemies.");
            timeTrialResultText.setFillColor(Color::Red);
        }
    }
}


// Update Function
void game::Update()
{
    game::pollEvent();

    if (inIntroScreen || isGameOver || showTimeTrialResult) return;

    //game logic

    PlayerMotion();

    
    Shooting();


    timeTrial();
    
    // Update and remove off-screen bullets logic
    updatingBullet();
    
    // Bullet-enemy collision logic
    bulletEnemyCollision();


    // Spawn enemy logic
    SpawnEnemy();


    gameEndCheck();

}




// Render game objects
void game::Render()
{
    if (inIntroScreen) {
        window->clear();

        // Draw intro background
        window->draw(introBackgroundSprite);

        // Draw title
        window->draw(titleText);

        // Draw buttons
        window->draw(playButton);
        window->draw(exitButton);
        window->draw(playText);
        window->draw(exitText);

        window->display();
        return;
    }








    this->window->clear();

     // Draw map
    this->window->draw(this->map);

    // Draw player
    this->window->draw(this->player.player);

    // Draw bullet
    for (auto& bullet : bullets)
        bullet.draw(*this->window);

    // draw Enemies
    for (auto& enemy : enemies)
    {
        enemy.draw(*this->window);
    }

    // draw health bar
    float healthPercent = static_cast<float>(player.getHealth()) / player.getMaxHealth();
    healthBar.setSize(Vector2f(200.f * healthPercent, 20.f));

    this->window->draw(healthBarBg);
    this->window->draw(healthBar);
    this->window->draw(healthLabel);

    // Draw Score
    this->window->draw(scoreText);

    // Draw time trial information
    if (isTimeTrialActive) {
        Text timeTrialText;
        timeTrialText.setFont(font);
        timeTrialText.setCharacterSize(24);
        timeTrialText.setFillColor(Color::White);
        timeTrialText.setPosition(20.f, 80.f);
        timeTrialText.setString("Time: " + to_string(static_cast<int>(timeTrialTimer)) +
            " | Kills: " + to_string(timeTrialKills) +
            "/" + to_string(timeTrialTarget));
        window->draw(timeTrialText);
    }

    // Draw time trial result if active
    if (showTimeTrialResult) {
        // Semi-transparent overlay
        RectangleShape overlay(Vector2f(window->getSize().x, window->getSize().y));
        overlay.setFillColor(Color(0, 0, 0, 200));
        window->draw(overlay);

        window->draw(timeTrialResultText);
        window->draw(continueButton);
        window->draw(continueText);
        window->display();
        return;
    }

    if (isGameOver) {
        window->clear();

        window->draw(introBackgroundSprite);

        // Draw Game Over title
        window->draw(gameOverText);

        // Draw buttons
        window->draw(playAgainButton);
        window->draw(exitButton);
        window->draw(playAgainText);
        window->draw(exitText);

        window->display();
        return;
    }
        

    this->window->display();
}


