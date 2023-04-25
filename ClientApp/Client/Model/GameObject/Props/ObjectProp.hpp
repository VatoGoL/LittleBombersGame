#pragma once
#include "../../Engine/Object.hpp"

class ObjectProp: public Object{
protected:
    int _health;
    vector2d_t _position;
public:
    virtual void init() override;
    virtual void update() override;
    
    virtual ~ObjectProp();
};
