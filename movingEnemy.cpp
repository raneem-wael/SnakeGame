#include "movingEnemy.h"

void movingEnemy::initShape()
{
	this->shape.setFillColor(sf::Color::Black);
}

movingEnemy::movingEnemy()
{
}

movingEnemy::~movingEnemy()
{
}

void movingEnemy::update()
{
}

void movingEnemy::render(sf::RenderTarget& target)
{

	target.draw(this->shape);
}
