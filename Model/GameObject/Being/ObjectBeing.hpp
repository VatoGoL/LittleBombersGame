#pragma once
#include "../../Engine/Object.hpp"

class ObjectBeing: public Object{
protected:
    int _health;
    vector2d_t _position;
    int _speed;
public:
    virtual void init() override;
    virtual void update() override;
    
    virtual ~ObjectBeing();
};
