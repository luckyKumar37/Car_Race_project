#include "Player.h"



Player::Player() = default;


Player::~Player()
{
    delete animation;
}

Vector2f Player::getPosition()
{
    return player.getPosition();
}

bool Player::isAlive() const {
    return alive;
}

Vector2f Player::getSize()
{
    return Vector2f(player.getGlobalBounds().width , player.getGlobalBounds().height);
}

void Player::takeDamage(int damage) {
    if (!alive) return;

    health -= damage;
    if (health <= 0) {
        health = 0;
        alive = false;
        cout << "Player has died!" << endl;
    }
}

void Player::reset() {
    health = 100;
    alive = true;
    player.setPosition(30, 700);
}

void Player::updateHealth(float dt)
{
    if (health < maxHealth)
    {
        healthRegenTimer += dt;
        if (healthRegenTimer >= healthRegenCooldown)
        {
            health += 5;
            if (health > maxHealth) health = maxHealth;
            healthRegenTimer = 0.f;
        }
    }
}

void Player::updatePosition(float x, float y)
{
    this->player.move(x, y);

    // Updating direction based on movement
    if (x > 0 && currentDirection != Right)
        setDirection(Right);
    else if (x < 0 && currentDirection != Left)
        setDirection(Left);
    else if (y > 0 && currentDirection != Down)
        setDirection(Down);
    else if (y < 0 && currentDirection != Up)
        setDirection(Up);
}

void Player::initPlayer()
{
    // loading player texture
    if (this->playerT.loadFromFile("Asset/player.png") == false)
    {
        cout << "Failed to load player\n";
        return;
    }

    this->player.setTexture(playerT);
    this->player.setScale(1.5, 1.5);
    this->player.setPosition(30, 700);

    // Initialize animation
    animation = new Animation(&player, &playerT, 0.2f);

    // Adding frames for walking up 
    for (int i = 0; i < 9; i++)
        animation->addUpFrame(IntRect(i * 64, 0, 64, 64));

    // Adding frames for walking left 
    for (int i = 0; i < 9; i++)
        animation->addLeftFrame(IntRect(i * 64, 64, 64, 64));

    // Adding frames for walking down 
    for (int i = 0; i < 9; i++)
        animation->addDownFrame(IntRect(i * 64, 128, 64, 64));

    // Adding frames for walking right 
    for (int i = 0; i < 9; i++)
        animation->addRightFrame(IntRect(i * 64, 192, 64, 64));

    currentDirection = Right;
    animation->setDirection("Right"); 

    health = 100;
    maxHealth = 100;
    healthRegenTimer = 0.f;
    healthRegenCooldown = 3.f; 

}

void Player::setDirection(Direction direction)
{
    if (currentDirection != direction)
    {
        currentDirection = direction;

        // Updating the animation frames based on direction
        switch (direction)
        {
        case Up:
            animation->setDirection("Up");
            break;
        case Left:
            animation->setDirection("Left");
            break;
        case Down:
            animation->setDirection("Down");
            break;
        case Right:
            animation->setDirection("Right");
            break;
        }
    }
}


void Player::setStaticFrame()
{
    int row = 0;
    switch (currentDirection)
    {
    case Up: row = 0; break;
    case Left: row = 1; break;
    case Down: row = 2; break;
    case Right: row = 3; break;
    }

    // Setting the sprite to the first frame of the current direction
    this->player.setTextureRect(IntRect(0, row * 64, 64, 64));
}


void Player::updateAnimation(float deltaTime)
{
    animation->update(deltaTime);
}

int Player::getHealth()
{
    return health;
}

int Player::getMaxHealth() 
{ 
    return maxHealth;
}

