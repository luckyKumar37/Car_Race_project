#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"



using namespace sf;
using namespace std;

class game
{
private:
    // window
    RenderWindow* window;

    // Event
    Event event;


    // Font
    Font font;

    // Map
    Texture mapT;
    Sprite map;

    // Player
    Player player;

    // Enemies
    vector<Enemy> enemies;

    int maxEnemies = 5;           
    const int maxAllowedEnemies = 20; 
    float enemyCapTimer = 0.f;     

    float spawnTimer = 0.f;
    float spawnInterval = 2.f; 
    float difficultyTimer = 0.f; 
    float spawnIntervalMin = 0.4f;




    // bullet
    vector<Bullet> bullets;




    // health bar
    RectangleShape healthBarBg;
    RectangleShape healthBar;


    // player Score
    int score;
    Text scoreText;
    Text healthLabel;

    // Play button
    RectangleShape playButton;
    Text playText;

    // Exit Button
    RectangleShape exitButton;
    Text exitText;

    bool isGameOver;
    bool inIntroScreen;

    // Initialize functions
    void initVariable();
    void intitWindow();
    void intitSprite();

public:
    // Constructor and Destructor
    game();
    ~game();

    // Functions
    bool iswindowopen() const;
    void pollEvent();
    void Update();
    void Render();


};



