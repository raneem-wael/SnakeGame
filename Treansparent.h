/*#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Obstacle.h"
#include"Player.h"
#include"Game.h"
#pragma once
#include"Food2.h"
#include"MovingObstacles.h"
class Treansparent
{
public:
    Treansparent();

    void initTra(float radius, const sf::Vector2f& initialPosition);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::CircleShape shape;
    sf::Vector2f position;
    sf::Vector2f targetPosition;
    size_t currentPoint;
    float speed = 150.f; // The speed of the obstacle (pixels per second)
};*/