#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Obstacle.h"  // For obstacle collision check

class Food {
public:
    enum class Type {
        FOOD1,
        FOOD2,
        FOOD3
    };

private:
    sf::CircleShape foodShape;    // The shape of the food
    Type foodType;                // The type of food (FOOD1, FOOD2, FOOD3)
    static const float radius;    // The radius of the food

public:
    Food(float x, float y, Type type);
    void render(sf::RenderTarget* target);
    void setPosition(float x, float y);
    sf::CircleShape& getShape();
    Type getType() const;
    static bool checkCollision(const sf::CircleShape& foodShape, const std::vector<Obstacle*>& obstacles);
};
