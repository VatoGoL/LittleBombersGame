#pragma once
#include "../ObjectProp.hpp"

class Wall: public ObjectProp{
public:
    Wall(int start_health, vector2d_t position);
    virtual void init() override;
    virtual void update() override;
    
    virtual ~Wall();
};