#pragma once
#include "Player.h"
#include"Game.h"
void Player::initSnake(){
    
    this->snakeBody.push_back(sf::CircleShape(20.f));  // Initial snake head
    this->snakeBody[0].setFillColor(sf::Color::White);
    this->snakeBody[0].setPosition(sf::Vector2f(15.f, 15.f));
}

void Player::initVariables(){
   
    this->moveSpeed = 3.f;
}

//Player::Player()
Player::Player(float x, float y) : currentDirection(Direction::None), moveSpeed(3.f) {
    initVariables();
    initSnake();
}

Player::~Player(){

}

void Player::update(sf::RenderTarget* target, const std::vector<Obstacle*>& obstacles){//, const std::vector<Obstacle>& obstacles
    
    this->snakeMove();
    this->wallCollision(target);
    this->checkObstacleCollision(obstacles);
}

void Player::render(sf::RenderTarget* target) {
   
    for (auto& segment : this->snakeBody) {
        target->draw(segment);
    }

}

void Player::wallCollision(sf::RenderTarget* target) {
    // Check collision for the head of the snake
    if (!snakeBody.empty()) {
        sf::CircleShape& head = snakeBody[0];
        float radius = head.getRadius();

        // Left wall collision (handled as per your code)
        if (head.getPosition().x < 15.f) {
            head.setPosition(15.f, head.getPosition().y);  // Keep it at the left border
        }

        // Right wall collision
        if (head.getPosition().x + radius >= target->getSize().x - 35.f) {
            head.setPosition(target->getSize().x - radius - 35.f, head.getPosition().y);  // Keep it within the right border
        }

        // Top wall collision
        if (head.getPosition().y < 15.f) {
            head.setPosition(head.getPosition().x, 15.f);  // Keep it at the top border
        }

        // Bottom wall collision
        if (head.getPosition().y + radius > target->getSize().y - 35.f) {
            head.setPosition(head.getPosition().x, target->getSize().y - radius - 35.f);  // Keep it within the bottom border
        }
    }
}


void Player::checkObstacleCollision(const std::vector<Obstacle*>& obstacles) {
    for (const auto& obstacle : obstacles) {
        for (auto& segment : this->snakeBody) {
            if (segment.getGlobalBounds().intersects(obstacle->getShape().getGlobalBounds())) {
                // Handle collision (e.g., game over or reset position)
                this->snakeBody.clear();  // Clear snake body
                this->initSnake();  // Re-initialize snake
                break;
            }
        }
    }
}





void Player::snakeMove()
{
    // Update the direction based on key presses
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        currentDirection = Direction::Left;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        currentDirection = Direction::Right;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        currentDirection = Direction::Up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        currentDirection = Direction::Down;
    }

    // Move the snake body
    for (int i = snakeBody.size() - 1; i > 0; i--) {
        snakeBody[i].setPosition(snakeBody[i - 1].getPosition());
    }

    // Move the head based on the current direction
    switch (currentDirection) {
    case Direction::Left:
        snakeBody[0].move(-moveSpeed, 0.f);
        break;
    case Direction::Right:
        snakeBody[0].move(moveSpeed, 0.f);
        break;
    case Direction::Up:
        snakeBody[0].move(0.f, -moveSpeed);
        break;
    case Direction::Down:
        snakeBody[0].move(0.f, moveSpeed);
        break;
    case Direction::None:
        // Do nothing if no direction is set
        break;
    }
}


void Player::grow(int amount) {
    for (int i = 0; i < amount; i++) {
        // Add new segment to the snake at the last position
        sf::CircleShape newSegment(20.f);
        newSegment.setFillColor(sf::Color::White);
        newSegment.setPosition(snakeBody.back().getPosition());  // New segment follows last segment
        snakeBody.push_back(newSegment);
    }
}

void Player::increaseSpeed() {
    moveSpeed += 0.3f;  // Increase snake's speed by 1
}

