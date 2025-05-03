#pragma once
#include <SFML/Graphics.hpp>

class Obstacle {
protected:
    sf::RectangleShape obstacleShape;  // Shape for the obstacle

public:
    Obstacle(float x, float y, float width, float height) {
        obstacleShape.setSize(sf::Vector2f(width, height));
        obstacleShape.setPosition(x, y);
        obstacleShape.setFillColor(sf::Color::Black);  // Color of the obstacle
    }
    virtual ~Obstacle(){}

    virtual void update() {}  // Virtual update function (could be used in MovingObstacle)

    void render(sf::RenderTarget* target) {
        target->draw(obstacleShape);  // Draw the obstacle on the screen
    }

    sf::RectangleShape& getShape() {
        return obstacleShape;  // Provide access to the shape for collision detection
    }
    

};