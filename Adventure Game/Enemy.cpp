#include "Enemy.h"
#include <cmath>
#include <cstdlib>

Enemy::Enemy()
{
    // choosing random sides for different shapes
    int sides = rand() % 4 + rand()%6 + 2; 
    float radius = 30.f;

    shape = CircleShape(radius, sides);
    shape.setFillColor(Color::Green);
    shape.setOrigin(radius, radius);
    shape.setPosition(400.f, 300.f);

    speed = 6.f;
}

void Enemy::setPosition(Vector2f pos)
{
    shape.setPosition(pos);
}

void Enemy::update(Vector2f playerPos)
{
    Vector2f dir = playerPos - shape.getPosition();
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (len > 0.f)
    {
        dir /= len;
        shape.move(dir * speed);
    }
}

void Enemy::draw(RenderWindow& window)
{
    window.draw(shape);
}

Vector2f Enemy::getPosition()
{
    return shape.getPosition();
}

Vector2f Enemy::getSize()
{
    return Vector2f(shape.getGlobalBounds().width, shape.getGlobalBounds().height);
}

FloatRect Enemy::getBounds() const
{
    return shape.getGlobalBounds();
}



