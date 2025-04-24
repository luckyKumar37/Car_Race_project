#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"

using namespace std;
using namespace sf;

class Player
{
public:
    // Texture and Sprite
    Texture playerT;
    Sprite player;

    // Animation
    Animation* animation;

    // Directions
    enum Direction { Up, Left, Down, Right };
    Direction currentDirection;

    // Initialize player
    void initPlayer();

    // Constructor and Destructor
    Player();
    ~Player();

    // Functions
    Vector2f getPosition();
    Vector2f getSize();
    void updatePosition(float x, float y);
    void setDirection(Direction direction);
    void setStaticFrame();
    void updateAnimation(float deltaTime);
    int getHealth();
    int getMaxHealth();
    bool isAlive() const;
    void takeDamage(int damage);
    void updateHealth(float dt);
    void reset();

private:
    int health;
    int maxHealth;
    float healthRegenTimer;
    float healthRegenCooldown;
    bool alive = true;
};


