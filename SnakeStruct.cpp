#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

struct Game {
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;
};




enum class Direction { None, Up, Down, Left, Right };


struct Snake {
    std::vector<sf::CircleShape> body;
    Direction currentDirection = Direction::None;
    float moveSpeed = 3.f;
};

struct Obstacle {
    sf::RectangleShape shape;  
    Obstacle(float x, float y, float width, float height) {
        shape.setSize(sf::Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Black);  
    }

   
    void render(sf::RenderWindow& window) const {
        window.draw(shape);  
    }

    
    sf::RectangleShape& getShape() {
        return shape;  
    }
};

struct MovingObstacle {
    sf::RectangleShape shape;
    sf::Vector2f direction;  
    float moveSpeed;         
    MovingObstacle(float x, float y, float width, float height, float speed, sf::Vector2f dir) {
        shape.setSize(sf::Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Black);  
        moveSpeed = speed;
        direction = dir;
    }

    
};

struct Food {
    enum class Type { FOOD1, FOOD2, FOOD3 };

    sf::CircleShape foodShape;
    Type foodType;

    static const float radius;

    // Constructor to create food with a type
    Food(float x, float y, Type type) : foodType(type) {
        foodShape.setRadius(radius);
        foodShape.setPosition(x, y);

        // Set color based on food type
        switch (foodType) {
        case Type::FOOD1:
            
            foodShape.setFillColor(sf::Color(156, 5, 40, 255));
            //foodShape.setFillColor(sf::Color::Green);
            break;
        case Type::FOOD2:
            foodShape.setFillColor(sf::Color(2, 97, 75,255));
            //foodShape.setFillColor(sf::Color::Red);
            break;
        case Type::FOOD3:
            foodShape.setFillColor(sf::Color(33, 0, 64, 255));
            //foodShape.setFillColor(sf::Color::Yellow);
            break;
        }
    }

    // Function to render food
    

    // Function to check if food collides with obstacles
    static bool checkCollision(const sf::CircleShape& foodShape, const std::vector<Obstacle*>& obstacles) {
        sf::CircleShape enlargedFoodShape = foodShape;
        enlargedFoodShape.setRadius(foodShape.getRadius() + 30.f); // Enlarged for detection
        enlargedFoodShape.setPosition(foodShape.getPosition());

        for (const auto& obstacle : obstacles) {
            const sf::RectangleShape& obstacleShape = obstacle->getShape();
            if (enlargedFoodShape.getGlobalBounds().intersects(obstacleShape.getGlobalBounds())) {
                return true;  // Collision detected
            }
        }

        return false;  // No collision
    }
};

const float Food::radius = 15.f;

// Function to initialize the window
void initWindow(Game& game) {
    game.videoMode.height = 600;
    game.videoMode.width = 900;
    game.window = new sf::RenderWindow(game.videoMode, "Snake Game", sf::Style::Close | sf::Style::Titlebar);
    game.window->setFramerateLimit(60);
}
void updateMovingObstacles(std::vector<MovingObstacle>& movingObstacles, const sf::RenderWindow& window) {
    for (auto& movingObstacle : movingObstacles) {
        // Get the current position of the obstacle
        sf::Vector2f position = movingObstacle.shape.getPosition();
        sf::Vector2f size = movingObstacle.shape.getSize();

        // Horizontal boundary check (left and right)
        if (position.x <= 0 || position.x + size.x >= window.getSize().x) {
            movingObstacle.direction.x = -movingObstacle.direction.x;  // Reverse the horizontal direction
        }

        // Vertical boundary check (top and bottom)
        if (position.y <= 0 || position.y + size.y >= window.getSize().y) {
            movingObstacle.direction.y = -movingObstacle.direction.y;  // Reverse the vertical direction
        }

        // Move the obstacle
        movingObstacle.shape.move(movingObstacle.direction * movingObstacle.moveSpeed);
    }
}

bool isPositionValid(const sf::Vector2f& position, const std::vector<Obstacle>& obstacles) {
    for (const auto& obstacle : obstacles) {
        if (obstacle.shape.getGlobalBounds().contains(position)) {
            return false;          }
    }
    return true;  
}

void initObstacles(std::vector<Obstacle>& obstacles, std::vector<MovingObstacle>& movingObstacles) {
    // Add static obstacles to the vector
    obstacles.push_back(Obstacle(100.f, 100.f, 50.f, 50.f));  // Example of a static obstacle
    obstacles.push_back(Obstacle(400.f, 400.f, 60.f, 60.f));  // Another static obstacle
    movingObstacles.push_back(MovingObstacle(200.f, 200.f, 50.f, 50.f, 1.f, sf::Vector2f(1.f, 0.f)));  // Horizontal
    movingObstacles.push_back(MovingObstacle(300.f, 300.f, 50.f, 50.f, 1.f, sf::Vector2f(0.f, 1.f)));  // Vertical

}


/*void spawnFood(std::vector<Food>& foods, const std::vector<Obstacle>& obstacles) {
    float x, y;
    bool collisionDetected = false;

    while (!collisionDetected) {
        x = static_cast<float>(rand() % (900 - 40) + 20);  
        y = static_cast<float>(rand() % (600 - 40) + 20);  
        collisionDetected = isPositionValid(sf::Vector2f(x, y), obstacles);
    }

        Food::Type foodType = Food::Type::FOOD1; 

    
    int foodTypeChance = rand() % 10;
    if (foodTypeChance >= 5) {
        foodType = Food::Type::FOOD2;  
    }
    else if (foodTypeChance == 6) {
        foodType = Food::Type::FOOD3;      }

    
    foods.push_back(Food(x, y, foodType));
}*/

void spawnFood(std::vector<Food>& foods, const std::vector<Obstacle>& obstacles) {
    
    static int food1Counter = 0;
    float x, y;
    bool collisionDetected = false;

    while (!collisionDetected) {
        x = static_cast<float>(rand() % (900 - 40) + 20);
        y = static_cast<float>(rand() % (600 - 40) + 20);
        collisionDetected = isPositionValid(sf::Vector2f(x, y), obstacles);
    }

    Food::Type foodType;

    // Sequence logic for food types
    if (food1Counter < 5) {
        foodType = Food::Type::FOOD1; // First 5 appearances of FOOD1
        food1Counter++;
    }
    else if (food1Counter == 5) {
        foodType = Food::Type::FOOD3; // FOOD3 appears once after 5 FOOD1
        food1Counter++;
    }
    else if (food1Counter < 8) {
        foodType = Food::Type::FOOD1; // Next 2 appearances of FOOD1
        food1Counter++;
    }
    else {
        foodType = Food::Type::FOOD2; // FOOD2 appears once after next 2 FOOD1
        food1Counter = 0; // Reset counter after sequence completes
    }

    // Add the food to the list
    foods.push_back(Food(x, y, foodType));
}



void initSnake(Snake& snake, float startX, float startY) {
    snake.body.push_back(sf::CircleShape(20.f));  // Initial snake head
    snake.body[0].setFillColor(sf::Color::White);
    snake.body[0].setPosition(sf::Vector2f(startX, startY));
}
void grow(Snake& snake, int amount) {
    for (int i = 0; i < amount; i++) {
        sf::CircleShape newSegment(20.f);
        newSegment.setFillColor(sf::Color::White);
        newSegment.setPosition(snake.body.back().getPosition());  // New segment follows last segment
        snake.body.push_back(newSegment);
    }
}

// Increase the snake's speed
void increaseSpeed(Snake& snake) {
    snake.moveSpeed += 0.3f;  // Increase speed by 0.3 units
}

// Handle food consumption by the snake
void handleFoodConsumption(Snake& snake, std::vector<Food>& foods, std::vector<Obstacle>& obstacles) {
    for (size_t i = 0; i < foods.size(); ++i) {
        if (snake.body[0].getGlobalBounds().intersects(foods[i].foodShape.getGlobalBounds())) {
            // Snake eats the food
            switch (foods[i].foodType) {
            case Food::Type::FOOD1:
                grow(snake, 3);  // Increase snake size by 1
                break;
            case Food::Type::FOOD2:
                increaseSpeed(snake);  // Increase snake's speed
                break;
            case Food::Type::FOOD3:
                grow(snake, 5);  // Increase snake size by 2
                break;
            }

            // Remove the consumed food and spawn new food
            foods.erase(foods.begin() + i);
            spawnFood(foods, obstacles);  // Spawn new food
            break;  // Exit the loop as the food has been consumed
        }
    }
}


// Function to handle window events
void pollEvents(Game& game) {
    while (game.window->pollEvent(game.event)) {
        switch (game.event.type) {
        case sf::Event::Closed:
            game.window->close();
            break;
        case sf::Event::KeyPressed:
            if (game.event.key.code == sf::Keyboard::Escape) {
                game.window->close();
            }
            break;
        }
    }
}

// Function to draw the border (using a text file)
void drawBorder(sf::RenderWindow* window, const std::string& filename) {
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

// Function to update the game logic (not much in this step yet)
void update(Game& game) {
    pollEvents(game);
    
}

void renderSnake(sf::RenderWindow& window, const Snake& snake) {
    for (const auto& segment : snake.body) {
        window.draw(segment);
    }
}

void renderObstacles(sf::RenderWindow& window, const std::vector<Obstacle>& obstacles) {
    for (const auto& obstacle : obstacles) {
        obstacle.render(window);  // Draw each obstacle
    }
}

void renderMovingObstacles(sf::RenderWindow& window, const std::vector<MovingObstacle>& movingObstacles) {
    for (const auto& movingObstacle : movingObstacles) {
        window.draw(movingObstacle.shape);  // Render each moving obstacle
    }
}
void renderFood(sf::RenderWindow& window, const std::vector<Food>& foods) {
    for (const auto& food : foods) {
        window.draw(food.foodShape);  // Drawing each food
    }
    
}
// Function to render the game window
void render(Game& game, Snake& snake, const std::vector<Obstacle>& obstacles, const std::vector<MovingObstacle>& movingObstacles, const std::vector<Food>&foods) {
    game.window->clear(sf::Color(168, 121, 111, 255));  // Clear window with a background color
    drawBorder(game.window, "border.txt");
    renderSnake(*game.window, snake);
    renderFood(*game.window, foods);
    // Call renderObstacles only once, without a loop inside
    renderObstacles(*game.window, obstacles);  // Draw all obstacles
    renderMovingObstacles(*game.window, movingObstacles);
   

    game.window->display();  // Display the rendered window
}




void updateSnakeDirection(Snake& snake) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        snake.currentDirection = Direction::Left;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        snake.currentDirection = Direction::Right;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        snake.currentDirection = Direction::Up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        snake.currentDirection = Direction::Down;
    }
}


void moveSnake(Snake& snake) {
    
    for (int i = snake.body.size() - 1; i > 0; i--) {
        snake.body[i].setPosition(snake.body[i - 1].getPosition());
    }

    
    switch (snake.currentDirection) {
    case Direction::Left:
        snake.body[0].move(-snake.moveSpeed, 0.f);
        break;
    case Direction::Right:
        snake.body[0].move(snake.moveSpeed, 0.f);
        break;
    case Direction::Up:
        snake.body[0].move(0.f, -snake.moveSpeed);
        break;
    case Direction::Down:
        snake.body[0].move(0.f, snake.moveSpeed);
        break;
    case Direction::None:
        // Do nothing if no direction is set
        break;
    }
}

// Function to render the snake to the window


// Function to update the snake (this includes handling input, movement, etc.)
void updateSnake(Snake& snake) {
    updateSnakeDirection(snake);  // Handle direction based on input
    moveSnake(snake);             // Move the snake based on the current direction
}


// Function to prevent the snake from going out of bounds
void wallCollision(Snake& snake, sf::RenderTarget* target) {
    if (!snake.body.empty()) {
        sf::CircleShape& head = snake.body[0];  // Access the snake's head (first segment)
        float radius = head.getRadius();        // Get the radius of the head

        // Left wall collision (ensure the snake's head doesn't go past the left border)
        if (head.getPosition().x < 15.f) {
            head.setPosition(15.f, head.getPosition().y);  // Keep it at the left border
        }

        // Right wall collision (ensure the snake's head doesn't go past the right border)
        if (head.getPosition().x + radius >= target->getSize().x - 35.f) {
            head.setPosition(target->getSize().x - radius - 35.f, head.getPosition().y);  // Keep it within the right border
        }

        // Top wall collision (ensure the snake's head doesn't go past the top border)
        if (head.getPosition().y < 15.f) {
            head.setPosition(head.getPosition().x, 15.f);  // Keep it at the top border
        }

        // Bottom wall collision (ensure the snake's head doesn't go past the bottom border)
        if (head.getPosition().y + radius > target->getSize().y - 35.f) {
            head.setPosition(head.getPosition().x, target->getSize().y - radius - 35.f);  // Keep it within the bottom border
        }
    }
}


void checkCollision(Snake& snake, const std::vector<Obstacle>& obstacles, const std::vector<MovingObstacle>& movingObstacles) {
    for (const auto& obstacle : obstacles) {
        if (snake.body[0].getGlobalBounds().intersects(obstacle.shape.getGlobalBounds())) {
            // If snake's head collides with any obstacle, reset snake
            snake.body.clear();
            snake.body.push_back(sf::CircleShape(20.f));  // Reinitialize head
            snake.body[0].setFillColor(sf::Color::White);
            snake.body[0].setPosition(15.f, 15.f);
        }
    }
    for (const auto& movingObstacle : movingObstacles) {
        if (snake.body[0].getGlobalBounds().intersects(movingObstacle.shape.getGlobalBounds())) {
            // If snake's head collides with a moving obstacle, reset snake
            snake.body.clear();
            snake.body.push_back(sf::CircleShape(20.f));  // Reinitialize head
            snake.body[0].setFillColor(sf::Color::White);
            snake.body[0].setPosition(15.f, 15.f);
        }
    }
}







int main() {

    std::cout << "Welcome to Snake Game :) \n You can move using arrows or (w,a,d,s) \n Collect food (circle dots) \n To close the game press Esc\nEnjoy Playing ^^ :)\n";
    std::srand(static_cast<unsigned>(std::time(0)));


    Game game;
    std::vector<Obstacle> obstacles;
    std::vector<MovingObstacle> movingObstacles;

    initWindow(game);

    Snake snake;
    initSnake(snake, 25.f, 25.f);
    initObstacles(obstacles, movingObstacles);

    std::vector<Food> foods;  // Container to store foods

    spawnFood(foods, obstacles);

    while (game.window->isOpen()) {
        update(game);  // Update the game state (handle events, etc.)
        updateSnake(snake);
        updateMovingObstacles(movingObstacles, *game.window);
        wallCollision(snake, game.window);

        checkCollision(snake, obstacles, movingObstacles);
        handleFoodConsumption(snake, foods, obstacles);
        render(game, snake, obstacles, movingObstacles, foods);  // Render the updated state to the window

    }

    // Clean up
    delete game.window; // Clean up dynamically allocated memory for the window
    return 0;

}