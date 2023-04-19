#pragma once 
#include "../ObjectBeing.hpp"

class Player: public ObjectBeing{
public:
    Player(int start_health, vector2d_t start_position, int speed);

    virtual void init() override;
    virtual void update() override;

    virtual ~Player();
};