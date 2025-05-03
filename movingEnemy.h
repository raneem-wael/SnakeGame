#pragma once
#include "Player.h"
class movingEnemy
{

private:
	sf::RectangleShape shape;
	void initShape();

public:
	movingEnemy();
	virtual ~movingEnemy();


	void update();
	void render(sf::RenderTarget& target);
};

