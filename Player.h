#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <cstdlib>  
#include <ctime>
#include"Obstacle.h"


class Player
{

private:
	
	
	enum class Direction {
		None,
		Left,
		Right,
		Up,
		Down
	};

	Direction currentDirection;
	
	void initSnake();
	void initVariables();

public:
	std::vector<sf::CircleShape> snakeBody;
	float moveSpeed;
	Player(float x = 50.f, float y = 50.f);
	virtual ~Player();
	void update(sf::RenderTarget* target, const std::vector<Obstacle*>& obstacles);
	void render(sf::RenderTarget *target);
	void wallCollision(sf::RenderTarget* target);
	void checkObstacleCollision(const std::vector<Obstacle*>& obstacles);
	void snakeMove();
	void grow(int amount = 1);  // Grow the snake
	void increaseSpeed();  // Increase snake speed
	//void grow();

};

