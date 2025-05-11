#pragma once

#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
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

    // Audio
    SoundBuffer shootBuffer;
    Sound shootSound;

    // Music
    Music backgroundMusic;
    float musicVolume;
    float sfxVolume;


    // bullet
    vector<Bullet> bullets;


    // intro page
    Texture introBackgroundTexture;
    Sprite  introBackgroundSprite;

    // title text
    Text titleText;

    // game over text
    Text gameOverText;

    // playagain button
    RectangleShape playAgainButton;
    Text playAgainText;


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

    // time trial variable
    bool isTimeTrialActive; // Whether the time trial is active
    float timeTrialTimer;   // Time remaining for the trial
    int timeTrialTarget;    // Target number of enemies to kill
    int timeTrialKills;     // Current number of enemies killed



    bool showTimeTrialResult;
    Text timeTrialResultText;
    RectangleShape continueButton;
    Text continueText;


    // Exit Button
    RectangleShape exitButton;
    Text exitText;

    bool isShooting;
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
    void PlayerMotion();
    void Shooting();
    void bulletEnemyCollision();
    void SpawnEnemy();
    void updatingBullet();
    void gameEndCheck();
    void timeTrial();
    void startTimeTrial(float duration, int targetKills);
    void initAudio();
    void playSound(Sound& sound);
    void pollEvent();
    void Update();
    void Render();


};



