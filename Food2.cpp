#pragma once
#include "Food2.h"
#include <cstdlib>  // For rand() function
#include <ctime>    // For random seed

// Food radius
const float Food::radius = 15.f;

Food::Food(float x, float y, Type type) : foodType(type) {
    foodShape.setRadius(radius);
    foodShape.setPosition(x, y);

    // Set a random color for different types of food
    switch (foodType) {
    case Type::FOOD1:
        foodShape.setFillColor(sf::Color::Green);  // FOOD1 - Green
        break;
    case Type::FOOD2:
        foodShape.setFillColor(sf::Color::Red);    // FOOD2 - Red
        break;
    case Type::FOOD3:
        foodShape.setFillColor(sf::Color::Yellow);   // FOOD3 - Yellow
        break;
    }
}

void Food::render(sf::RenderTarget* target) {
    target->draw(foodShape);
}

void Food::setPosition(float x, float y) {
    foodShape.setPosition(x, y);
}

sf::CircleShape& Food::getShape() {
    return foodShape;
}

Food::Type Food::getType() const {
    return foodType;
}



bool Food::checkCollision(const sf::CircleShape& foodShape, const std::vector<Obstacle*>& obstacles) {
    

    sf::CircleShape enlargedFoodShape = foodShape;
    enlargedFoodShape.setRadius(foodShape.getRadius() + 30.f);
    enlargedFoodShape.setPosition(foodShape.getPosition());

   

    for (const auto& obstacle : obstacles) {
        if (obstacle != nullptr) {
            // Make sure obstacle has a valid shape
            const sf::RectangleShape& obstacleShape = obstacle->getShape();
            if (obstacleShape.getOrigin() != sf::Vector2f(35.f, 35.f)) {
               
                continue;
            }

            // Log obstacle details
           

            if (enlargedFoodShape.getGlobalBounds().intersects(obstacleShape.getGlobalBounds())) {
                return true;  // Food collides with obstacle
            }
        }
        
    }

    return false;
}
