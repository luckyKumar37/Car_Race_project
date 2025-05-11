#include "Bullet.h"
#include <cmath>

Bullet::Bullet(Vector2f startPos, Vector2f targetPos)
{
    this->shape.setRadius(5.f);
    this->shape.setFillColor(Color::Red);
    this->shape.setPosition(startPos);

    this->maxSpeed = 15.f;

    // Calculate normalized direction
    Vector2f direction = targetPos - startPos;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
        direction /= length;

    this->velocity = direction * maxSpeed;
}

void Bullet::update()
{
    this->shape.move(this->velocity);
}

void Bullet::draw(RenderWindow& window)
{
    window.draw(this->shape);
}

FloatRect Bullet::getBounds() const
{
    return shape.getGlobalBounds();
}
