#pragma once
#include <iostream>
#include <format>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "movingEnemy.h"
#include "Obstacle.h"
#include "MovingObstacles.h"
#include "Food2.h"
//#include "Treansparent.h"


#include<memory>

class Game
{
private:

	// variables
	std::vector<Food*> foods;  // Vector for holding food objects
	int food1Counter;          // Count of FOOD1 eaten
	int food2Counter;          // Count of FOOD2 eaten
	
	void spawnFood();          
	void handleFoodConsumption();
	std::vector<Obstacle*> obstacles;			   // Static obstacles vector
	std::vector<MovingObstacle> movingObstacles;  // Moving obstacles vector
	 
	std::vector<std::unique_ptr<Obstacle>> obstacles0;		
											
	Player player;

	sf::Event event;
	sf::VideoMode videoMode;
	sf::RectangleShape enemy;
	
	
	// functions
	void initWindow();
	void initVariables();
	void initEnemy();
	void initObstacles();  // Function to initialize obstacles

public:
	
	//Treansparent obstacleT;
	sf::RenderWindow* window;
	Game();
	virtual ~Game();
	const bool running() const;
	
	// functions
	void pollEvents();
	void update();
	void render();
	void drawBorder(sf::RenderWindow* window, const std::string& filename);
	bool isPositionValid(const sf::Vector2f& position, const sf::Vector2f& size);
	

};








/*#pragma once
#include<iostream>
#include <format>
#include <vector>
#include<string>
#include <fstream>
#include "Player.h"
#include "movingEnemy.h"
#include "Obstacle.h" 
#include "MovingObstacles.h"



class Game
{
private:
	
	//variables
	std::vector<Obstacle*> obstacles;  
	Player player;
	std::vector<MovingObstacles> movingBalls;
	
	
	sf::Event event;
	sf::VideoMode videoMode;
	

	//game objects
	
	sf::RectangleShape enemy;
	
	
	//functions
	void initWindow();
	void initVariables();
	void initEnemy();
	
public:
	//constructor and deconstructor
	sf::RenderWindow* window;
	Game();
	virtual ~Game();
	
	
	//Accessors
	
	const bool running() const;
	
	//functions
	void pollEvents();
	void update();
	void render();
	void drawBorder(sf::RenderWindow* window, const std::string& filename);
	void initObstacles();
};

*/
