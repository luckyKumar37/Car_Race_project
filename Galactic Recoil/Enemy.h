#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Enemy {
private:
    CircleShape shape;
    float speed;

public:
    Enemy();
    void setPosition(Vector2f pos);
    void update(Vector2f playerPos);
    void draw(RenderWindow& window);
    Vector2f getPosition();
    Vector2f getSize();
    FloatRect getBounds() const;
};




