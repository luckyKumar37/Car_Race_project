#include "game.h"
#include <cstdlib>
#include <ctime>


// Initialize variables
void game::initVariable()
{
    /*this->window = nullptr;*/
    game::intitSprite();
    this->player.initPlayer();
    cout << "init works\n";

    healthBarBg.setSize(Vector2f(200.f, 20.f));
    healthBarBg.setFillColor(Color::Red);
    healthBarBg.setPosition(20.f, 20.f);

    healthBar.setSize(Vector2f(200.f, 20.f));
    healthBar.setFillColor(Color::Green);
    healthBar.setPosition(20.f, 20.f);


    score = 0;

    // Load font
    if (!font.loadFromFile("Asset/ARIALNI.ttf")) {
        std::cout << "Failed to load font!\n";
    }

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
    game::initVariable();
    game::intitWindow();
    
}

// Destructor
game::~game()
{
    delete this->window;
}


// Check if the window is open
bool game::iswindowopen() const
{
    return this->window->isOpen();
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
            }
            else if (exitButton.getGlobalBounds().contains(mousePos))
            {
                window->close();
            }
        }
        else if (isGameOver && event.type == Event::MouseButtonPressed)
        {
            Vector2f mousePos = window->mapPixelToCoords(Mouse::getPosition(*window));
            if (playButton.getGlobalBounds().contains(mousePos))
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
            }
            else if (exitButton.getGlobalBounds().contains(mousePos))
            {
                window->close();
            }
        }
    }
}



// Update Function
void game::Update()
{
    game::pollEvent();

    if (inIntroScreen || isGameOver) return;

    //game logic

    // Player Movement Logic
    float moveX = 0.f, moveY = 0.f;
    bool isMoving = false;

    sf::Vector2f playerPos = this->player.getPosition();
    sf::Vector2u windowSize = this->window->getSize();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && playerPos.y > 0)
    {
        moveY = -5.f;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && playerPos.x > 0)
    {
        moveX = -5.f;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && playerPos.y < windowSize.y - this->player.getSize().y)
    {
        moveY = 5.f;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && playerPos.x < windowSize.x - this->player.getSize().x)
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

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2f playerCenter = player.getPosition() + player.getSize() / 2.f;
        sf::Vector2i mousePosScreen = sf::Mouse::getPosition(*this->window);
        sf::Vector2f mousePosWorld = this->window->mapPixelToCoords(mousePosScreen);

        bullets.emplace_back(playerCenter, mousePosWorld);
    }
    
    // Update and remove off-screen bullets logic
    for (int i = 0; i < bullets.size(); ) {
        bullets[i].update();

        sf::FloatRect bounds = bullets[i].getBounds();
        if (bounds.left + bounds.width < 0 || bounds.left > window->getSize().x ||
            bounds.top + bounds.height < 0 || bounds.top > window->getSize().y)
        {
            bullets.erase(bullets.begin() + i);
        }
        else {
            ++i;
        }
    }
    
    // Bullet-enemy collision logic
    for (int i = 0; i < bullets.size(); ) {
        bool bulletRemoved = false;

        for (int j = 0; j < enemies.size() && !bulletRemoved; ) {
            if (bullets[i].getBounds().intersects(enemies[j].getBounds())) {
         
                bullets.erase(bullets.begin() + i);
                enemies.erase(enemies.begin() + j);
                score++;

                scoreText.setString("Score: " + std::to_string(score));
                bulletRemoved = true;
            }
            else {
                ++j;
            }
        }

        if (!bulletRemoved) ++i;
    }


    // Spawn enemy logic
    spawnTimer += 0.016f;
    difficultyTimer += 0.016f;
    enemyCapTimer += 0.016f;
    if (spawnTimer >= spawnInterval && enemies.size() < maxEnemies) {
        spawnTimer = 0.f;

        Enemy enemy;
        float randX = static_cast<float>(std::rand() % 900 + 50);
        float randY = static_cast<float>(std::rand() % 600 + 50);
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
        if (enemy.getBounds().intersects(FloatRect(player.getPosition(), player.getSize()))) {
            player.takeDamage(5); 

            // enemy bounce away after hitting the player
            Vector2f pushDir = enemy.getPosition() - player.getPosition();
            float len = std::sqrt(pushDir.x * pushDir.x + pushDir.y * pushDir.y);
            if (len != 0)
            {
                pushDir /= len;
                enemy.setPosition(enemy.getPosition() + pushDir * 100.f); 
            }
            cout << "Player health: " << player.getHealth() << endl;
        }
    }


    if (!player.isAlive()) {
        cout << "Game Over! Player has died." << endl; 
        cout << "Player Score: " << score << endl;
        isGameOver = true;
        return;
    }

}




// Render game objects
void game::Render()
{
    // render for intro screen and game over screen
    if (inIntroScreen || isGameOver) {
        window->clear(Color(10, 10, 30));
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
        

    this->window->display();
}


