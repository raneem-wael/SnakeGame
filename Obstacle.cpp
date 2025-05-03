#include "Obstacle.h"








/*#include "Obstacle.h"




Obstacle::Obstacle(float x, float y, float sizeX, float sizeY, bool moveHorizontally)
{
    this->obstacleShape.setSize(sf::Vector2f(sizeX, sizeY));
    this->obstacleShape.setPosition(x, y);
    this->obstacleShape.setFillColor(sf::Color::Red); // Color for obstacles

    this->moveSpeed = 50.f;  // Speed of movement
    this->isMovingHorizontally = moveHorizontally;  // Set if it moves horizontally or vertically
}

void Obstacle::update(float deltaTime, float windowWidth, float windowHeight)
{
    // Horizontal movement
    if (this->isMovingHorizontally) {
        this->obstacleShape.move(this->moveSpeed * deltaTime, 0.f);

        // Bounce off the left and right edges
        if (this->obstacleShape.getPosition().x <= 0.f || this->obstacleShape.getPosition().x + this->obstacleShape.getSize().x >= windowWidth) {
            this->moveSpeed = -this->moveSpeed;  // Reverse direction when hitting left or right
        }
    }
    // Vertical movement
    else {
        this->obstacleShape.move(0.f, this->moveSpeed * deltaTime);

        // Bounce off the top and bottom edges
        if (this->obstacleShape.getPosition().y <= 0.f || this->obstacleShape.getPosition().y + this->obstacleShape.getSize().y >= windowHeight) {
            this->moveSpeed = -this->moveSpeed;  // Reverse direction when hitting top or bottom
        }
    }
}

void Obstacle::render(sf::RenderWindow& window)
{
    window.draw(this->obstacleShape);
}

const  sf::RectangleShape& Obstacle::getShape() const
{
    return this->obstacleShape;  
}
*/