#pragma once
#include"Obstacle.h"
#include "MovingObstacles.h"

void MovingObstacle::update() {
    sf::Vector2f position = obstacleShape.getPosition();
    sf::Vector2f size = obstacleShape.getSize();

    // Check horizontal boundary for bouncing
    if (moveHorizontal) {
        if (position.x <= 0 || position.x + size.x >= 900) {
            speed = -speed;  // Reverse direction when hitting left or right borders
        }
        obstacleShape.move(speed, 0.f);
    }
    // Check vertical boundary for bouncing
    else {
        if (position.y <= 0 || position.y + size.y >= 600) {
            speed = -speed;  // Reverse direction when hitting top or bottom borders
        }
        obstacleShape.move(0.f, speed);
    }
}
