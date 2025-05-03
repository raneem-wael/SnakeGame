/*#pragma once
#include "Treansparent.h"
#include <cmath>

Treansparent::Treansparent() : shape(10.f), position(0.f, 0.f), targetPosition(0.f, 0.f), currentPoint(0) {
    shape.setFillColor(sf::Color(255, 255, 255, 128)); // White with transparency
    shape.setPosition(position);
}

void Treansparent::initTra(float radius, const sf::Vector2f& initialPosition) {
    shape.setRadius(radius);
    position = initialPosition;
    targetPosition = initialPosition;
    currentPoint = 0;
    shape.setPosition(position);
    shape.setFillColor(sf::Color(255, 255, 255, 128));
}

void Treansparent::update(float deltaTime) {
    std::vector<sf::Vector2f> path = {
        sf::Vector2f(900.f / 2.f, 0.f),
        sf::Vector2f(900.f, 600.f / 2.f),
        sf::Vector2f(900.f / 2.f, 600.f),
        sf::Vector2f(0.f, 600.f / 2.f)
    };

    sf::Vector2f direction = targetPosition - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 1.f) {
        currentPoint = (currentPoint + 1) % path.size();
        targetPosition = path[currentPoint];
    }

    if (distance > 0.f) {
        direction /= distance;
        position += direction * speed * deltaTime;
    }

    shape.setPosition(position);
}

void Treansparent::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

/*
class Treansparent
{
public:
    Treansparent() : shape(10.f), position(0.f, 0.f), targetPosition(0.f, 0.f), currentPoint(0) {
        shape.setFillColor(sf::Color(255, 255, 255, 128)); // White with transparency
        shape.setPosition(position);
    };

    void initTra(float radius, const sf::Vector2f& initialPosition) {
        shape.setRadius(radius);  // Set radius for the shape
        position = initialPosition;  // Set the position
        targetPosition = initialPosition;  // Set the target position
        currentPoint = 0;  // Reset the current point
        shape.setPosition(position);  // Set the position of the shape
        shape.setFillColor(sf::Color(255, 255, 255, 128)); // White with transparency
    };

    void update(float deltaTime)  {//, sf::RenderTarget& window
        // Define the diamond path (midpoints of the window sides)
       

        std::vector<sf::Vector2f> path = {
            sf::Vector2f(900.f/ 2.f, 0.f), // Top
            sf::Vector2f(900.f, 600.f/ 2.f), // Right
            sf::Vector2f(900.f/ 2.f, 600.f), // Bottom
            sf::Vector2f(0.f, 600.f / 2.f) // Left
        };

        // Move the obstacle towards its target position
        sf::Vector2f direction = targetPosition - position;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance < 1.f) {
            // Once we are close enough to the target, move to the next point in the path
            currentPoint = (currentPoint + 1) % path.size();
            targetPosition = path[currentPoint];
        }

        // Normalize direction and move the obstacle
        if (distance > 0.f) {
            direction /= distance;  // Normalize
            position += direction * speed * deltaTime;  // Move the obstacle
        }

        shape.setPosition(position);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

private:
    sf::CircleShape shape;
    sf::Vector2f position;
    sf::Vector2f targetPosition;
    size_t currentPoint;
    float speed = 150.f; // The speed of the obstacle (pixels per second)
};

*/