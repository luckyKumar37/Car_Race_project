#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bullet {
private:
    CircleShape shape;
    Vector2f velocity;
    float maxSpeed;

public:
    Bullet(Vector2f startPos, Vector2f targetPos);

    void update();
    void draw(RenderWindow& window);

    FloatRect getBounds() const;
};


