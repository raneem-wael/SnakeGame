#pragma once
#include "Obstacle.h"

class MovingObstacle : public Obstacle {
private:
    float speed;              
    bool moveHorizontal;      
public:
    MovingObstacle(float x, float y, float width, float height, float speed, bool moveHorizontal)
        : Obstacle(x, y, width, height), speed(speed), moveHorizontal(moveHorizontal) {}

    void update() override; //{
       


};
