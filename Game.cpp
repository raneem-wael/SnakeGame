#pragma once
#include "Game.h"
#include "Obstacle.h"
#include"MovingObstacles.h"
#include"Player.h"
#include"Food2.h"

#include <cstdlib> 

void Game::initWindow(){

	this->videoMode.height = 600;
	this->videoMode.width = 900;
	//this to get the resolution of the screen this->videoMode.getDesktopMode();
	this->window = new sf::RenderWindow(this->videoMode, "Snake Game", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60); 
     

}

void Game::initVariables(){

	this->window = nullptr;
}

void Game::initEnemy()
{
    
    this->enemy.setPosition(std::rand() % (this->window->getSize().x - static_cast<int>(enemy.getSize().x)),
                            std::rand() % (this->window->getSize().y - static_cast<int>(enemy.getSize().y)));
    this->enemy.setSize(sf::Vector2f(60.f, 60.f));
    this->enemy.setFillColor(sf::Color::Black);
}



Game::Game():food1Counter(0), food2Counter(0){
   
	this-> initVariables();
	this->initWindow();
    this->initEnemy();
    this->initObstacles();
    this->spawnFood();
   //this->obstacleT.initTra(20.f, sf::Vector2f(900.f / 2.f, 0.f));
}

Game::~Game(){
    for (auto& obstacle : obstacles) {
        delete obstacle;  // Delete each obstacle
    }
    obstacles.clear();
	delete this->window;
   // delete food;

}
//Accessors

const bool Game::running() const
{	
	
	return this->window->isOpen();
}




bool Game::isPositionValid(const sf::Vector2f& position, const sf::Vector2f& size) {
    for (const auto& obstacle : obstacles) {
        if (obstacle->getShape().getGlobalBounds().intersects(sf::FloatRect(position, size))) {
            return false;  // Position overlaps with an obstacle
        }
    }
    return true;
}

void Game::spawnFood() {
    float x, y;
    bool collisionDetected = false;
    sf::Vector2f foodPosition;

    while (!collisionDetected) {
        // Randomize food position within the game window
        foodPosition.x = static_cast<float>(rand() % (window->getSize().x - 40) + 20);
        foodPosition.y = static_cast<float>(rand() % (window->getSize().y - 40) + 20);

        // Check if the position is valid
        collisionDetected = isPositionValid(foodPosition, sf::Vector2f(20.f, 20.f));  // Assuming food size is 20x20
    }
    Food::Type foodType = Food::Type::FOOD1;  // Default food is FOOD1

    // Randomly decide the type of food based on counters
    if (food1Counter >= 3) {
        foodType = Food::Type::FOOD2;  // Spawn FOOD2 after 10 FOOD1s
        food1Counter = 0;  // Reset FOOD1 counter
    }
    else if (food2Counter >= 2) {
        foodType = Food::Type::FOOD3;  // Spawn FOOD3 after 5 FOOD1s
        food2Counter = 0;  // Reset FOOD2 counter
    }

    // Try generating food until it doesn't collide with walls or obstacles
    do {
        x = std::rand() % (this->window->getSize().x - 40) + 20;  // Random x position
        y = std::rand() % (this->window->getSize().y - 40) + 20;  // Random y position
        Food tempFood(x, y, foodType);
        collisionDetected = Food::checkCollision(sf::CircleShape(30.f), obstacles); // Check collision with obstacles
    } while (collisionDetected);

    // Create the food object and add it to the vector
    foods.push_back(new Food(x, y, foodType));
}
;




void Game::handleFoodConsumption() {
    for (auto& food : foods) {
        if (this->player.snakeBody[0].getGlobalBounds().intersects(food->getShape().getGlobalBounds())) {
            // Player eats the food
            if (food->getType() == Food::Type::FOOD1) {
                this->player.grow();  // Increase the snake size
                food1Counter++;
            }
            else if (food->getType() == Food::Type::FOOD2) {
                this->player.increaseSpeed();  // Increase the snake's speed
                food2Counter++;
            }
            else if (food->getType() == Food::Type::FOOD3) {
                this->player.grow(2);  // Increase snake size by 2
                
            }

            // Remove food from the screen and spawn a new one
            delete food;
            food = nullptr;
            spawnFood();  // Spawn new food
        }
    }

    // Remove any null food (if any) from the foods vector
    foods.erase(std::remove(foods.begin(), foods.end(), nullptr), foods.end());
}
void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape) {
                this->window->close();
            }
       
        }

    }
}

void Game::drawBorder(sf::RenderWindow* window, const std::string& filename)
{


    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::string line;
    int row = 0;

    // Read each line from the file
    while (std::getline(file, line)) {
        for (int col = 0; col < line.length(); ++col) {
            if (line[col] == '#') {
                sf::RectangleShape tile(sf::Vector2f(15.f, 15.f));  // Tile size for the border
                tile.setFillColor(sf::Color::Black);  // Set border color to black
                tile.setPosition(col * 15.f, row * 15.f);  // Set position based on row and col
                window->draw(tile);  // Draw the tile
            }
        }
        row++;
    }

    file.close();
}





void Game::initObstacles() {
    // Static obstacles
    obstacles.push_back(new Obstacle(100.f, 100.f, 50.f, 50.f));  // Example of static obstacle
    obstacles.push_back(new Obstacle(400.f, 400.f, 60.f, 60.f));  // Another static obstacle
    
    
    // Moving obstacles (horizontal and vertical)
    obstacles.push_back(new MovingObstacle(200.f, 200.f, 50.f, 50.f, 2.f, true));  // Horizontal movement
    obstacles.push_back(new MovingObstacle(300.f, 300.f, 50.f, 50.f, 2.f, false)); // Vertical movement
}

void Game::update() {
    // Update all obstacles
    for (auto& obstacle : obstacles) {
        obstacle->update();  // Call update on each obstacle (static ones will do nothing)
    }
  //  sf::Clock clock;
  //  float deltaTime = clock.restart().asSeconds();
    this->pollEvents();
    this->player.update(this->window, obstacles);  // Update player
    this->player.checkObstacleCollision(obstacles);
    this->handleFoodConsumption();
   // this->obstacleT.update(deltaTime);

}

void Game::render() {
    this->window->clear(sf::Color(168, 121, 111, 255));
    this->drawBorder(this->window, "border.txt");
    // Render all obstacles
    for (auto& obstacle : obstacles) {
        obstacle->render(this->window);  // Draw each obstacle (static and moving)
    }

    // Render player, etc.
    //this->window->draw(this->food->getShape());
    for (auto& food : foods) {
        food->render(this->window);  // Draw food on screen
    }
    this->player.render(this->window);

    this->window->display();
}
